#ifndef UserDto_hpp
#define UserDto_hpp

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"
#include <iostream>
#include OATPP_CODEGEN_BEGIN(DTO)
/*  
ENUM(Role, v_int32,
     VALUE(GUEST, 0, "ROLE_GUEST"),
     VALUE(ADMIN, 1, "ROLE_ADMIN")
)
*/
class UserDto : public oatpp::DTO {
  
  DTO_INIT(UserDto, DTO)

  DTO_FIELD(Int32, id);
 // DTO_FIELD(Int32, UserId);
  DTO_FIELD(String, name, "name");
  DTO_FIELD(String, surname, "surname");
  DTO_FIELD(String, role, "role");
 // DTO_FIELD(String, time, "time");
  DTO_FIELD(String, RFID, "RFID");

};

#include OATPP_CODEGEN_END(DTO)

#endif /* UserDto_hpp */
