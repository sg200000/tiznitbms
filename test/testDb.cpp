#include <filesystem>
#include <gtest/gtest.h>
#include "dbFactory.hpp"

namespace fs = std::filesystem;

fs::path root = "data";
fs::path artifacts = "artifacts";

class TestDb : public testing::Test {
protected:
    void SetUp() override {
        this->_db = DbFactory::createDb(DbFactory::SQLITE3, "test");
        _tableCreated = this->_db->executeSqlFile(root / "test.sql");
        _dataFetched = this->_db->execute("SELECT * FROM test");
    }

    void insertDataInExistingFields(){
        this->_dataInserted = this->_db->insertData("test", {
            {"firstName","Said"},
            {"lastName","Guouihaj"}
        });
    }

    void insertDataInNonExistingFields(){
        this->_dataInserted = this->_db->insertData("test", {
            {"phone","0147852369"},
        });
    }    

    void requestExistingData(){
        std::unordered_map<std::string,std::string> condition = {};
        std::cout << "size : " << condition.size() << std::endl;
        this->_dataFetched = this->_db->requestData("test", {"firstName"},condition, &(this->outData));
    }

    void requestNonExistingData(){
        this->_dataFetched = this->_db->requestData("test", {"firstName"},{{"id","-1"}}, &(this->outData));
    }

    void updateExistingData(){
        this->_dataUpdated = this->_db->updateData("test",{{"firstName", "ali"}}, {{"id","1"}});
    }

    void updateNonExistingData(){
        this->_dataUpdated = this->_db->updateData("test",{{"phone", "0123654789"}}, {{"id","1"}});
    }

    void deleteExistingData(){
        this->_dataDeleted = this->_db->deleteData("test",{{"id","1"}});
    }

    void deleteNonExistingData(){
        this->_dataDeleted = this->_db->deleteData("test",{{"id","-1"}});
    }
    
    static void TearDownTestCase() {
        if (fs::exists("test.db")){
            fs::remove("test.db");
        }
    }

    std::unique_ptr<DBManager> _db;
    bool _tableCreated;
    bool _dataFetched;
    bool _dataInserted;
    bool _dataDeleted;
    bool _dataUpdated;
    std::vector<std::vector<std::string>> outData;
};

TEST_F(TestDb, basicFunctionality){
    ASSERT_NE(_db,nullptr);
    ASSERT_TRUE(_tableCreated);
    EXPECT_TRUE(_dataFetched);
}

TEST_F(TestDb, insertData){
    insertDataInExistingFields();
    EXPECT_TRUE(_dataInserted);
    insertDataInNonExistingFields();
    EXPECT_FALSE(_dataInserted);
}

TEST_F(TestDb, requestData){
    requestExistingData();
    EXPECT_NE(outData.size(),0);
    EXPECT_TRUE(_dataFetched);
    outData.clear();
    requestNonExistingData();
    EXPECT_EQ(outData.size(),0);
    EXPECT_FALSE(_dataFetched);
}

TEST_F(TestDb, updateData){
    updateExistingData();
    EXPECT_TRUE(_dataUpdated);
    updateNonExistingData();
    EXPECT_FALSE(_dataUpdated);
}

TEST_F(TestDb, deleteData){
    deleteExistingData();
    EXPECT_TRUE(_dataDeleted);
    deleteNonExistingData();
    EXPECT_FALSE(_dataDeleted);
}

