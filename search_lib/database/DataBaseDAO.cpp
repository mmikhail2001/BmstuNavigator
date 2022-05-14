#include "DataBaseDAO.h"
#include "DataBaseConfigReader.h"

DataBaseDAO *DataBaseDAO::dataBaseDao = nullptr;
DataBaseConnection *DataBaseDAO::dataBaseConnection = nullptr;

DataBaseDAO *DataBaseDAO::getInstance() {
    if (dataBaseDao == nullptr) {
        dataBaseDao = new DataBaseDAO();
        //DataBaseConfigReader dataBaseConfigReader;
        DataBaseConfig *dataBaseConfig = new DataBaseConfig("localhost", "root", "admin", "bmstuNavigator");

        std::cout << "config = " << dataBaseConfig->databaseName << std::endl;
        dataBaseConnection = new DataBaseConnection(dataBaseConfig);
    }

    return dataBaseDao;
}

std::vector<BasePoint> DataBaseDAO::getBasePoints() {
    MYSQL_RES *res = performQuery("SELECT * FROM points WHERE isInfr = 0;");
    std::cout << ("Database Output:\n") << std::endl;
    MYSQL_ROW row; // The results rows (array)

    std::vector<BasePoint> vector = {};

    while ((row = mysql_fetch_row(res)) != NULL) {
        // the below row[] parametes may change depending on the size of the table and your objective
        std::cout << row[0] << " | " << row[1] << std::endl;
        BasePoint basePoint(atoi(row[0]));
        /*
        std::string query = "SELECT * FROM edges WHERE from_fk = " + std::to_string(basePoint.GetId()) + ";";
        MYSQL_RES *res2 = performQuery(&query[0]);
        MYSQL_ROW row2; // The results rows (array)
        while ((row2 = mysql_fetch_row(res2)) != NULL) {
            // the below row[] parametes may change depending on the size of the table and your objective
            std::cout << row2[0] << " | " << row2[1] << " | " << row2[3] << std::endl;
        }
         */

        vector.push_back(basePoint);
    }

    MYSQL_RES *res2;
    MYSQL_RES *res3;
    for (BasePoint &b: vector) {
        std::string idStr = std::to_string(b.GetId());

        std::string query2 = "SELECT * FROM edges WHERE from_fk = " + idStr + ";";
        std::cout << "query = " << query2 << std::endl;
        res2 = performQuery(&query2[0]);
        MYSQL_ROW row2; // The results rows (array)
        while ((row2 = mysql_fetch_row(res2)) != NULL) {
            // the below row[] parametes may change depending on the size of the table and your objective
            std::cout << row2[0] << " | " << row2[1] << " | " << row2[2] << " | " << row2[3] << std::endl;
            Edge edge(atoi(row2[0]), atoi(row2[1]), atoi(row2[2]), row2[3]);
            b.AddEdge(edge);
            //Edge edge(atoi(row2[0]), 2, 2, "ghj");
        }

        std::string query3 = "SELECT * FROM point_names WHERE id_fk = " + idStr + ";";
        std::cout << "query = " << query3 << std::endl;
        res3 = performQuery(&query3[0]);
        MYSQL_ROW row3; // The results rows (array)
        while ((row3 = mysql_fetch_row(res3)) != NULL) {
            // the below row[] parametes may change depending on the size of the table and your objective
            std::cout << "name = " << row3[0] << " | " << row3[1] << std::endl;
            //Edge edge(atoi(row2[0]), atoi(row2[1]), atoi(row2[2]), row2[3]);
            b.AddName(row3[1]);
            //Edge edge(atoi(row2[0]), 2, 2, "ghj");
        }
    }

    /*
    std::cout << "The vector elements are : ";
    for (int i = 0; i < vector.size(); i++) {
        std::cout << vector.at(i).GetId() << " " << vector.at(i).GetEdges().at(0).linkToFile << " " << vector.at(i).GetEdgeById(vector.at(i).GetEdges().at(0).dist).linkToFile << ' ';
    }
    std::cout << std::endl;
    */

    // clean up the database result
    mysql_free_result(res);
    mysql_free_result(res2);
    mysql_free_result(res3);

    return vector;
}

std::vector<Infrastructure> DataBaseDAO::getInfrastructurePoints() {
    MYSQL_RES *res = performQuery("SELECT * FROM points WHERE isInfr = 1;");
    std::cout << ("Database Output:\n") << std::endl;
    MYSQL_ROW row; // The results rows (array)

    std::vector<Infrastructure> vector = {};

    while ((row = mysql_fetch_row(res)) != NULL) {
        // the below row[] parametes may change depending on the size of the table and your objective
        std::cout << row[0] << " | " << row[1] << std::endl;
        Infrastructure infrastructure(atoi(row[0]));
        /*
        std::string query = "SELECT * FROM edges WHERE from_fk = " + std::to_string(infrastructure.GetId()) + ";";
        MYSQL_RES *res2 = performQuery(&query[0]);
        MYSQL_ROW row2; // The results rows (array)
        while ((row2 = mysql_fetch_row(res2)) != NULL) {
            // the below row[] parametes may change depending on the size of the table and your objective
            std::cout << row2[0] << " | " << row2[1] << " | " << row2[3] << std::endl;
        }
         */

        vector.push_back(infrastructure);
    }

    MYSQL_RES *res2;
    MYSQL_RES *res3;
    for (Infrastructure &b: vector) {
        std::string idStr = std::to_string(b.GetId());

        std::string query2 = "SELECT * FROM edges WHERE from_fk = " + idStr + ";";
        std::cout << "query = " << query2 << std::endl;
        res2 = performQuery(&query2[0]);
        MYSQL_ROW row2; // The results rows (array)
        while ((row2 = mysql_fetch_row(res2)) != NULL) {
            // the below row[] parametes may change depending on the size of the table and your objective
            std::cout << row2[0] << " | " << row2[1] << " | " << row2[2] << " | " << row2[3] << std::endl;
            Edge edge(atoi(row2[0]), atoi(row2[1]), atoi(row2[2]), row2[3]);
            b.AddEdge(edge);
            //Edge edge(atoi(row2[0]), 2, 2, "ghj");
        }

        std::string query3 = "SELECT * FROM point_names WHERE id_fk = " + idStr + ";";
        std::cout << "query = " << query3 << std::endl;
        res3 = performQuery(&query3[0]);
        MYSQL_ROW row3; // The results rows (array)
        while ((row3 = mysql_fetch_row(res3)) != NULL) {
            // the below row[] parametes may change depending on the size of the table and your objective
            std::cout << "name = " << row3[0] << " | " << row3[1] << std::endl;
            //Edge edge(atoi(row2[0]), atoi(row2[1]), atoi(row2[2]), row2[3]);
            b.AddName(row3[1]);
            //Edge edge(atoi(row2[0]), 2, 2, "ghj");
        }
    }

    /*
    std::cout << "The vector elements are : ";
    for (int i = 0; i < vector.size(); i++) {
        std::cout << vector.at(i).GetId() << " " << vector.at(i).GetEdges().at(0).linkToFile << " " << vector.at(i).GetEdgeById(vector.at(i).GetEdges().at(0).dist).linkToFile << ' ';
    }
    std::cout << std::endl;
    */

    // clean up the database result
    mysql_free_result(res);
    mysql_free_result(res2);
    mysql_free_result(res3);

    return vector;
}

BasePoint DataBaseDAO::getBasePoint(unsigned int id) {
    // TODO
    return BasePoint(0);
};

unsigned int DataBaseDAO::addBasePoint(BasePoint basePoint) {
    // TODO
    return 0;
}

bool DataBaseDAO::updateBasePoint(BasePoint basePoint) {
    // TODO
    return false;
}

bool DataBaseDAO::removeBasePoint(unsigned int id) {
    // TODO
    return false;
}

Infrastructure DataBaseDAO::getInfrastructure(unsigned int id) {
    // TODO
    return Infrastructure(0);
}

unsigned int DataBaseDAO::addInfrastructure(Infrastructure infrastructure) {
    // TODO
    return 0;
}

bool DataBaseDAO::updateInfrastructure(Infrastructure infrastructure) {
    // TODO
    return false;
}

bool DataBaseDAO::removeInfrastructure(unsigned int id) {
    // TODO
    return false;
}

Edge DataBaseDAO::getEdge(unsigned int id) {
    // TODO
    return Edge();
}

unsigned int DataBaseDAO::addEdge(Edge edge) {
    // TODO
    return 0;
}

bool DataBaseDAO::updateEdge(Edge edge) {
    // TODO
    return false;
}

bool DataBaseDAO::removeEdge(unsigned int id) {
    // TODO
    return false;
}

User DataBaseDAO::getUserByLoginPassword(std::string login, std::string password) {
    // TODO
    return User();
}

MYSQL_RES *DataBaseDAO::performQuery(const char *sqlQuery) {
    //send query to db
    if (mysql_query(dataBaseConnection->connection, sqlQuery)) {
        std::cout << "MySQL Query Error: " << mysql_error(dataBaseConnection->connection) << std::endl;
        //exit(1);
    }

    return mysql_use_result(dataBaseConnection->connection);
}

DataBaseDAO::~DataBaseDAO() {
    //delete dataBaseConnection;
    delete dataBaseDao;
}

