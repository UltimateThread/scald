#include "MetaUtilities.h"

namespace SCALD_CORE::Utils {

   entt::id_type GetIdType(const sol::table& comp)
   {
      if (!comp.valid())
      {
         SCALD_ERROR("Failed to get the type id -- Component has not been exposed to lua!");
         assert(comp.valid() && "Failed to get the type id -- Component has not been exposed to lua!");
         return -1;
      }

      const auto func = comp["type_id"].get<sol::function>();
      assert(func.valid() &&
         "[type_id()] - function has not been exposed to lua!\n"
         "Please ensure all components and types have a type_d function\n"
         "when creating the new usertype."
      );

      return func.valid() ? func().get<entt::id_type>() : -1;
   }

}
