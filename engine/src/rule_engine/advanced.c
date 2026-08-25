#include "re_internal.h"
#include <string.h>

static int date_digit(const char *text, size_t index) {
    return text[index] >= '0' && text[index] <= '9';
}

int re_parse_date(const char *text, int64_t *out) {
    int year, month, day, hour, minute, second;
    static const int month_days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int64_t y, era, day_of_era, day_of_year, days;
    size_t i;
    if (text == NULL || out == NULL || strlen(text) != 20u || text[4] != '-' ||
        text[7] != '-' || text[10] != 'T' || text[13] != ':' ||
        text[16] != ':' || text[19] != 'Z') return 0;
    for (i = 0u; i < 20u; ++i)
        if (i != 4u && i != 7u && i != 10u && i != 13u && i != 16u && i != 19u && !date_digit(text, i)) return 0;
    year = (text[0] - '0') * 1000 + (text[1] - '0') * 100 + (text[2] - '0') * 10 + text[3] - '0';
    month = (text[5] - '0') * 10 + text[6] - '0';
    day = (text[8] - '0') * 10 + text[9] - '0';
    hour = (text[11] - '0') * 10 + text[12] - '0';
    minute = (text[14] - '0') * 10 + text[15] - '0';
    second = (text[17] - '0') * 10 + text[18] - '0';
    if (month < 1 || month > 12 || hour > 23 || minute > 59 || second > 59 ||
        day < 1 || day > month_days[month - 1] + (month == 2 && (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)))) return 0;
    y = year - (month <= 2);
    era = y >= 0 ? y / 400 : (y - 399) / 400;
    day_of_year = (153 * (month + (month > 2 ? -3 : 9)) + 2) / 5 + day - 1;
    day_of_era = (y - era * 400) * 365 + (y - era * 400) / 4 - (y - era * 400) / 100 + day_of_year;
    days = era * 146097 + day_of_era;
    *out = (days - 719468) * 86400 + hour * 3600 + minute * 60 + second;
    return 1;
}

re_status_t re_accumulator_evaluate(re_accumulator_kind_t kind, const re_value_t *values, size_t count, re_value_t *out) {
    size_t i; double result = 0.0; size_t numeric = 0u;
    if (out == NULL) return RE_STATUS_INVALID_ARGUMENT;
    if (kind == RE_ACCUM_COUNT) { out->type = RE_VALUE_INT64; out->as.int64_value = (int64_t)count; return RE_STATUS_OK; }
    if (kind < RE_ACCUM_SUM || kind > RE_ACCUM_MAX) return RE_STATUS_INVALID_ARGUMENT;
    if (count == 0u || values == NULL) return RE_STATUS_NOT_FOUND;
    for (i = 0u; i < count; ++i) {
        double value;
        if (values[i].type == RE_VALUE_INT64) value = (double)values[i].as.int64_value;
        else if (values[i].type == RE_VALUE_DOUBLE) value = values[i].as.double_value;
        else return RE_STATUS_INVALID_ARGUMENT;
        if (numeric == 0u) result = value;
        else if (kind == RE_ACCUM_SUM || kind == RE_ACCUM_AVERAGE) result += value;
        else if (kind == RE_ACCUM_MIN && value < result) result = value;
        else if (kind == RE_ACCUM_MAX && value > result) result = value;
        ++numeric;
    }
    if (kind == RE_ACCUM_AVERAGE) result /= (double)numeric;
    out->type = RE_VALUE_DOUBLE; out->as.double_value = result; return RE_STATUS_OK;
}

int re_rule_active(const re_rule_t *rule, int64_t now) {
    int64_t effective;
    int64_t expiry;
    if (rule == NULL) return 0;
    if (rule->effective_date != NULL && (!re_parse_date(rule->effective_date, &effective) || now < effective)) return 0;
    if (rule->expiry_date != NULL && (!re_parse_date(rule->expiry_date, &expiry) || now >= expiry)) return 0;
    return 1;
}
