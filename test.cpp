#include <stdio.h>
#include "sqlite3.h"
#include <iostream>
#include <string.h>
using namespace std;
//This function updates a character's stamina to a specified value
void update(sqlite3* db)
{
  string id;
  string stamina;
  cout << "What is the id of the character you wish to update?" << endl;
  std::cin >> id;
  cout << "What is the amount of stamina you would like to set this character to?" << endl;
  std::cin >> stamina;
  const char* sql_const = "UPDATE `characters` SET `stamina` = '";
  int size = strlen(sql_const);
  char sql[size];
  strcpy(sql, sql_const);
  strcat(sql, stamina.c_str());
  strcat(sql, "'");
  strcat(sql, " WHERE `id` = '");
  strcat(sql, id.c_str());
  strcat(sql, "'");
  cout << sql << endl;
  sqlite3_exec(db, sql, NULL, NULL, NULL);
}


//This function creates a new character
void create(sqlite3* db)
{ 
  const char* sql = "INSERT INTO `characters` VALUES ('1', '300' , '500', '1')";
  cout << sql << endl;
  sqlite3_exec(db, sql, NULL, NULL, NULL);
}


//This function deletes a character given an id
void ldelete(sqlite3* db)
{
  const char* sql = "DELETE FROM `characters` WHERE `id` = '4'";
  cout << sql << endl;
  sqlite3_exec(db, sql, NULL, NULL, NULL);
}

//This function is called after the SELECT sql command is executed. It will print out all the attributes for a character
static int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
  int i;
  for(i=0;i<argc;i++){
    printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
  }
  printf("\n");
  return 0;
}

//This function reads the character with id = 1
void select(sqlite3* db)
{
  const char* sql = "SELECT * FROM `characters` WHERE `id` = '1'";
  cout << sql << endl;
  sqlite3_exec(db, sql, callback, 0, NULL);
}
//INSERT, DELETE, UPDATE, SELECT
int main()
{
  sqlite3 *db;
  const char* filename = "test.db";
  int rc = sqlite3_open(filename, &db);
  if(rc)
    {
      cout << "Could not open database." << endl;
      return -1;
    }
  //update(db);
  //create(db);
  select(db);
  //ldelete(db);
  sqlite3_close(db);
  return 0;
}
