#include <iostream>
#include "ldbapi.h"

using namespace std;
using namespace ldbapi;

#define FILEPATH  "/home/youzp"
#define DBNAME    "test.ldb"

CLevelDb *g_pLdb = NULL;

void Init()
{
    if (NULL == g_pLdb)
    {
        g_pLdb = new CLevelDb();
    }
}

void Clear()
{
    if (g_pLdb)
    {
        delete g_pLdb;
        g_pLdb = NULL;
    }
}

void Test01()
{
    std::cout << "Enter Test01" << std::endl;

    bool bRes = false;

    /// Test Open
    bRes = g_pLdb->Open(FILEPATH, DBNAME);
    if (!bRes)
    {
        cout << "Open Fail" << endl;
        return;
    }
    else
    {
        cout << "Open OK" << endl;
    }

    /// Test Put
    bRes = g_pLdb->Put("Key1", "1234");
    if (!bRes)
    {
        cout << "Put Fail" << endl;
        return;
    }
    else
    {
        cout << "Put OK" << endl;
    }

    /// Test Get
    string sValue;
    bRes = g_pLdb->Get("Key1", sValue);
    if (!bRes)
    {
        cout << "Get Fail" << endl;
        return;
    }
    else
    {
        cout << "Value1:" << sValue << endl;
    }

    /// Test Delete
    bRes = g_pLdb->Delete("Key1");
    if (!bRes)
    {
        cout << "Delete Fail" << endl;
        return;
    }
    else
    {
        cout << "Delete OK" << endl;
    }

    std::cout << "Exit From Test01" << std::endl;
    return;
}

void Test02()
{
    std::cout << "Enter Test02" << std::endl;
    bool bRes = false;

    /// Test Put
    bRes = g_pLdb->Put("Key1", "1234");
    if (!bRes)
    {
        cout << "Put Fail" << endl;
        return;
    }
    else
    {
        cout << "Put OK" << endl;
    }

    /// Test WriteBatch
    leveldb::WriteBatch batch;
    batch.Delete("Key1");
    batch.Put("Key1", "1111");
    batch.Put("Key2", "2222");
    batch.Put("Key3", "3333");
    batch.Put("Key4", "4444");
    
    bRes = g_pLdb->WriteBatch(batch);
    if (!bRes)
    {
        cout << "WriteBatch Fail" << endl;
    }
    else
    {
        cout << "WriteBatch OK" << endl;
    }

    /// Test Get
    string sValue;
    bRes = g_pLdb->Get("Key4", sValue);
    if (!bRes)
    {
        cout << "Get Fail" << endl;
        return;
    }
    else
    {
        cout << "Value4:" << sValue << endl;
    }

    std::cout << "Exit From Test02" << std::endl;
    return;
}

int main()
{
    Init();

    Test01();

    cout << "*********" << endl;
    
    Test02();

    Clear();

    return 0;
}


