#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <pqxx/pqxx>
#include <string>

std::string get_database_url() {
    const char* db_url = std::getenv("DATABASE_URL");
    if (db_url == nullptr || db_url[0] == '\0') {
        throw std::runtime_error("DATABASE_URL environment variable not set.");
    }

    return db_url;
}

pqxx::connection connect_to_db() {
    return pqxx::connection(get_database_url());
}

bool add_image_entry(pqxx::connection& conn, const std::string& gcs_url, double latitude, double longitude) {
    try {
        pqxx::work txn(conn);
        txn.exec(
            "INSERT INTO images (gcs_url, latitude, longitude) "
            "VALUES ($1, $2, $3);",
            {gcs_url, latitude, longitude}
        );
        txn.commit();
        return true;
    } catch (const std::exception &e) {
        std::cerr << "Error adding image entry: " << e.what() << std::endl;
        return false;
    }
}

