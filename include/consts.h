//
// Created by catslashbin on 22-11-28.
//

#ifndef CYGNOIDES_DECISION_CONSTS_H
#define CYGNOIDES_DECISION_CONSTS_H

#define SMALL_ARMOR_WIDTH 130.6f
#define SMALL_ARMOR_HEIGHT 55.4f
#define BIG_ARMOR_WIDTH 231.0f
#define BIG_ARMOR_HEIGHT 55.4f

#define MAX_FACILITY_ID 13
enum FacilityID {
    UNKNOWN = 0,

    HERO_1 = 1,

    ENGINEER_2 = 2,
    STANDARD_3 = 3,

    STANDARD_4 = 4,
    STANDARD_5 = 5,
    SENTRY_7 = 7,

    BASE_8 = 8,
    OUTPOST_10 = 10,

    UNKNOWN_BOT = 11,
    UNKNOWN_STRUCTURE = 12
};

#endif //CYGNOIDES_DECISION_CONSTS_H
