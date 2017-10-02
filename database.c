#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>


// 1) Define MAX_DATA and MAX_ROWS
#define MAX_DATA 512
#define MAX_ROWS 100


typedef struct _address {
    int id, set;
    char name[MAX_DATA];
    char email[MAX_DATA];
} Address;


typedef struct _database {
    Address rows[MAX_ROWS];
} Database;


typedef struct _connection {
    FILE *file;
    Database *db;
} Connection;


void die(char *message) {
    if (errno) {
        perror(message);
    } else {
        printf("ERROR: %s\n", message);
    }
}


void Address_print(Address *address) {
    printf("id: %d, name: %s, email: %s\n", address->id, address->name,
           address->email);
}


void Database_load(Connection *conn) {
    int rowCount = fread(conn->db, sizeof(Database), sizeof(Address),
                         conn->file);

    if (!rowCount) {
        die("Failed to read Database!");
    }
}


Connection *Database_open(const char *filename, char mode) {
    Connection *conn = malloc(sizeof(Connection));
    if (!conn) die("Unable to create connection.");

    conn->db = malloc(sizeof(Database));
    if (!conn->db) die("Unable to create database.");

    if (mode == 'c') {
        conn->file = fopen(filename, "w");
    } else {
        conn->file = fopen(filename, "r+");

        if (conn->file) Database_load(conn);
    }

    if (!conn->file) die("Failed to open the file.");

    return conn;
}


void Database_close(Connection *conn) {
    if (conn) {
        fclose(conn->file);
        free(conn->db);
        free(conn);
    }
}


void Database_write(Connection *conn) {
    rewind(conn->file);

    int rowCount = fwrite(conn->db, sizeof(Database), 1, conn->file);
    if (rowCount != 1) die("Failed to write.");

    rowCount = fflush(conn->file);
    if (rowCount == -1) die("Failed to flush.");
}


void Database_create(Connection *conn) {
    for (int i = 0; i < MAX_ROWS; i++) {
        // Compound literal
        conn->db->rows[i] = (Address){.id = i, .set = 0};
    }
}


void Database_set(
        Connection *conn, int id, const char *name, const char *email) {
    Address *address = &conn->db->rows[id];

    if (address->set) {
        die("This has already been set!");
    } else {
        address->set = 1;
    }

    // strlcpy() is similar to strncpy() but copies at most size-1 bytes from
    // src to dst, and always adds a null terminator following the bytes copied
    // to dst - also returns a size_t/int and not the char array pointer.
    size_t result = strlcpy(address->name, name, MAX_DATA);
    if (!result) die("Failed to copy name");

    result = strlcpy(address->email, email, MAX_DATA);
    if (!result) die("Failed to copy email");
}


void Database_get(Connection *conn, int id) {
    Address *address = &conn->db->rows[id];

    if (address->set) {
        Address_print(address);
    } else {
        die("This row has not been set!");
    }
}


void Database_delete(Connection *conn, int id) {
    conn->db->rows[id] = (Address){.id = id, .set = 0};
}


void Database_list(Connection *conn) {
    Database *db = conn->db;

    for (int i = 0; i <= MAX_ROWS; i++) {
        Address *addr = &db->rows[i];
        if (addr->set) {
            Address_print(addr);
        }
    }
}


int main(int argc, char *argv[])
{
    if (argc < 3)
        die("USAGE: ex17 <dbfile> <action> [action params]");

    char *filename = argv[1];
    char action = argv[2][0];
    Connection *conn = Database_open(filename, action);
    int id = 0;

    if (argc > 3) id = atoi(argv[3]);
    if (id >= MAX_ROWS) die("There's not that many records.");

    switch (action) {
        case 'c':
            Database_create(conn);
            Database_write(conn);
            break;

        case 'g':
            if (argc != 4)
                die("Need an id to get");

            Database_get(conn, id);
            break;

        case 's':
            if (argc != 6)
                die("Need id, name, email to set");

            Database_set(conn, id, argv[4], argv[5]);
            Database_write(conn);
            break;

        case 'd':
            if (argc != 4)
                die("Need id to delete");

            Database_delete(conn, id);
            Database_write(conn);
            break;

        case 'l':
            Database_list(conn);
            break;
        default:
            die("Invalid action: c=create, g=get, s=set, d=del, l=list");
    }

    Database_close(conn);

    return 0;
}
