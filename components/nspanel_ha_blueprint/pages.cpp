// pages.cpp

#include "pages.h"

namespace nspanel_ha_blueprint {

    // Definition of the global current_page_id
    uint8_t current_page_id = 0;

    // Definition of the global next_page_id
    uint8_t next_page_id = UINT8_MAX;

    // Definition of the global previous_page_id
    uint8_t previous_page_id = 0;

    uint32_t ENTITY_PAGE_MASK = (1 << 18) | (1 << 19) | (1 << 20) | (1 << 21);
    uint32_t BUTTONS_PAGE_MASK = (1 << 12) | (1 << 13) | (1 << 14) | (1 << 15);
    uint32_t WEATHER_PAGE_MASK = (1 << 2) | (1 << 3) | (1 << 4) | (1 << 5) | (1 << 6);
    uint32_t ENTITY_ID_PAGE_MASK = (1 << 24) | (1 << 7) | (1 << 11) | (1 << 22) |
                                            (1 << 10) | (1 << 25) | (1 << 27) | (1 << 23);
    uint32_t NON_API_ID_PAGE_MASK = (1 << 0) | (1 << 1) | (1 << 8) | (1 << 9) | (1 << 26);

    // Implementation of is_page_in_group
    bool is_page_in_group(uint32_t group_mask, uint8_t page_id) {
        if (page_id >= sizeof(page_names) / sizeof(page_names[0])) {
            return false;  // Invalid page_id, safely return false
        }
        return (group_mask & (1 << page_id)) != 0;
    }

    // Implementation of get_page_id
    uint8_t get_page_id(const std::string& page_name) {
        for (uint8_t i = 0; i < sizeof(page_names) / sizeof(page_names[0]); ++i) {
            if (strcmp(page_names[i], page_name.c_str()) == 0) {
                return i;
            }
        }
        return UINT8_MAX;
    }

}  // namespace nspanel_ha_blueprint
