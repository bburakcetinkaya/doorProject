
#ifndef CRUD_USERDB_HPP
#define CRUD_USERDB_HPP

#include "dto/UserDto.hpp"
#include "oatpp-sqlite/orm.hpp"
#include <iostream>
#include OATPP_CODEGEN_BEGIN(DbClient) //<- Begin Codegen

/**
 * UserDb client definitions.
 */
class UserDb : public oatpp::orm::DbClient {
public:

  UserDb(const std::shared_ptr<oatpp::orm::Executor>& executor)
    : oatpp::orm::DbClient(executor)
  {

    oatpp::orm::SchemaMigration migration(executor);
    migration.addFile(1 /* start from version 1 */, DATABASE_MIGRATIONS "/001_init.sql");
    // TODO - Add more migrations here.
    migration.migrate(); // <-- run migrations. This guy will throw on error.

    auto version = executor->getSchemaVersion();
    OATPP_LOGD("UserDb", "Migration - OK. Version=%d.", version);

  }

  QUERY(createUser,
        "INSERT INTO AppUser"
        "(name, surname, role, RFID) VALUES "
        "(:user.name, :user.surname, :user.role, :user.RFID);",
        PARAM(oatpp::Object<UserDto>, user))

  QUERY(updateUser,
        "UPDATE AppUser "
        "SET "
        " name=:user.name, "
        " surname=:user.surname, "
        " role=:user.role, "
        " RFID=:user.RFID "
        "WHERE "
        " id=:user.id;",
        PARAM(oatpp::Object<UserDto>, user))

  QUERY(getUserByRFID,
        "SELECT * FROM AppUser WHERE RFID=:RFID;",
        PARAM(oatpp::String, RFID))
  
 //----------------------------------------------------------------------------------------------
      QUERY(getUserById,
          "SELECT * FROM AppUser WHERE id=:id;",
          PARAM(oatpp::Int32, id))
 //----------------------------------------------------------------------------------------------

  QUERY(getUsers,
        "SELECT * FROM AppUser LIMIT :limit OFFSET :offset;",
        PARAM(oatpp::UInt32, offset),
        PARAM(oatpp::UInt32, limit))

  QUERY(deleteUserByUserId,
      "DELETE FROM AppUser WHERE id=:id;",
        PARAM(oatpp::Int32, id))

    QUERY(getAllUsers,
        "SELECT * FROM AppUser")

};

#include OATPP_CODEGEN_END(DbClient) //<- End Codegen

#endif //CRUD_USERDB_HPP
