#ifndef NONSTD_STRING_UTILS_H
#define NONSTD_STRING_UTILS_H


#include <string>
#include <string_view>
#include <locale>
#include <vector>
#if __GNUC__ == 8 && __has_include(<charconv>)
  #define NONSTD_STRING_UTILS_CHARCONV
  #define NONSTD_STRING_UTILS_CHARCONV_INTEGRAL_TYPES_ONLY
  #include <charconv>
#endif


namespace nonstd::string_utils::detail
{


template<typename I, typename F> inline void transform(I start, I stop, F func)
{
  while (start != stop) {
    *start = func(*start);
    start++;
  }
}


#ifdef NONSTD_STRING_UTILS_CHARCONV
  template <typename T> inline T parse_number(std::string_view sv, int base = 10)
  {
    T value{};
    std::from_chars(sv.data(), sv.data() + sv.size(), value, base);
    return value;
  }
#endif  // NONSTD_STRING_UTILS_CHARCONV


template<typename I> inline bool compare(I a, I b, const I last)
{
  if (*a != *b)
    return false;

  while (b != last && *(++a) == *(++b));

  if (b == last)
    return true;

  return false;
}


template <typename T> std::vector<T> inline split_keep_empty(std::string_view sv,
    std::string_view token)
{
  std::size_t start = 0;
  auto i = sv.find(token);
  std::vector<T> parts;

  while (i != sv.npos) {
    parts.emplace_back(sv.substr(start, i - start));
    start = i + token.size();
    i = sv.find(token, start);
  }
  parts.emplace_back(sv.substr(start));

  return parts;
}


template <typename T> std::vector<T> inline split_ignore_empty(std::string_view sv,
    std::string_view token)
{
  std::size_t start = 0;
  auto i = sv.find(token);
  std::vector<T> parts;

  while (i != sv.npos) {
    if (auto len = i - start; len > 0)
      parts.emplace_back(sv.substr(start, len));
    start = i + token.size();
    i = sv.find(token, start);
  }
  if (sv.size() - start > 0)
    parts.emplace_back(sv.substr(start));

  return parts;
}


template <typename T> inline std::tuple<T, T> split_first(std::string_view sv,
    std::string_view token)
{
  if (auto i = sv.find(token); i != sv.npos) {
    return {T{sv.substr(0, i)}, T{sv.substr(i+token.size())}};
  }
  return {T{sv}, T{}};
}


template <typename T> inline std::tuple<T, T> split_last(std::string_view sv,
    std::string_view token)
{
  if (auto i = sv.rfind(token); i != sv.npos) {
    return {T{sv.substr(0, i)}, T{sv.substr(i+token.size())}};
  }
  return {T{sv}, T{}};
}


template <typename T> inline T before_first(std::string_view sv, std::string_view token)
{
  if (auto i = sv.find(token); i != sv.npos) {
    return T{sv.substr(0, i)};
  }
  return T{};
}


template <typename T> inline T before_last(std::string_view sv, std::string_view token)
{
  if (auto i = sv.rfind(token); i != sv.npos) {
    return T{sv.substr(0, i)};
  }
  return T{};
}


template <typename T> inline T after_first(std::string_view sv, std::string_view token)
{
  if (auto i = sv.find(token); i != sv.npos) {
    return T{sv.substr(i + token.size())};
  }
  return T{};
}


template <typename T> inline T after_last(std::string_view sv, std::string_view token)
{
  if (auto i = sv.rfind(token); i != sv.npos) {
    return T{sv.substr(i + token.size())};
  }
  return T{};
}


template <typename T> inline T between(std::string_view sv, std::string_view first_token,
    std::string_view second_token, bool greedy = false)
{
  if (auto i = sv.find(first_token), j = greedy ? sv.rfind(second_token) : sv.find(second_token);
      i != sv.npos && j != sv.npos && j > i) {
    return T{sv.substr(i + first_token.size(), j - i - first_token.size())};
  }
  return T{};
}


template <typename T> inline T rbetween(std::string_view sv, std::string_view first_token,
    std::string_view second_token, bool greedy = false)
{
  if (auto i = sv.rfind(first_token), j = greedy ? sv.find(second_token) : sv.rfind(second_token);
      i != sv.npos && j != sv.npos && j < i) {
    return T{sv.substr(j + first_token.size(), i - j - first_token.size())};
  }
  return T{};
}


inline std::string replace(std::string_view sv, std::string_view search_token,
    std::string_view replace_token)
{
  std::vector<std::size_t> positions;
  auto pos = sv.find(search_token);
  while (pos != sv.npos) {
    positions.push_back(pos);
    pos = sv.find(search_token, pos + search_token.size());
  }
  if (positions.empty())
    return std::string{sv};

  std::string result;
  auto n = positions.size();
  result.resize(sv.size() - search_token.size() * n + replace_token.size() * n);
  auto result_it = std::begin(result);
  auto source_it = std::begin(sv);
  for (auto p : positions) {
    result_it = std::copy(source_it, std::begin(sv) + p, result_it);
    result_it = std::copy(std::begin(replace_token), std::end(replace_token), result_it);
    source_it = std::begin(sv) + p + search_token.size();
  }
  if (result_it != std::end(result)) {
    std::copy(source_it, std::end(sv), result_it);
  }

  return result;
}


inline std::string replace_inplace(std::string_view sv, std::string_view search_token,
    std::string_view replace_token)
{
  std::string result{sv};
  auto result_it = std::begin(result);
  auto pos = sv.find(search_token);

  while (pos != sv.npos) {
    result_it = std::copy(std::begin(replace_token), std::end(replace_token), std::begin(result) + pos);
    pos = sv.find(search_token, pos + search_token.size());
  }

  return result;
}


}  // namepsace nonstd::string_utils::detail


// The following functions expect ASCII (or single byte) encoding
//

namespace nonstd::string_utils::ascii  
{


inline void to_upper(std::string& s)
{
  detail::transform(std::begin(s), std::end(s), ::toupper);
}


inline void to_lower(std::string& s)
{
  detail::transform(std::begin(s), std::end(s), ::tolower);
}


inline std::string as_upper(std::string_view sv)
{
  std::string s{sv};
  detail::transform(std::begin(s), std::end(s), ::toupper);
  return s;
}


inline std::string as_lower(std::string_view sv)
{
  std::string s{sv};
  detail::transform(std::begin(s), std::end(s), ::tolower);
  return s;
}


// Splits sv each character_count characters, skipping skip characters after each split
// E.g.: split(sv, 3)    : "abcdef123"   -> "abc", "def" and "123"
//       split(sv, 3, 1) : "abc,def,123" -> "abc", "def" and "123"
inline std::vector<std::string_view> split(std::string_view sv, std::size_t character_count,
    std::size_t skip = 0)
{
  if (character_count == 0)
    return {};

  std::vector<std::string_view> v;
  auto size = sv.size();
  std::size_t i = 0;
  while (i < size) {
    v.push_back(sv.substr(i, character_count));
    i += character_count + skip;
  }

  return v;
}


}  // namespace nonstd::string_utils::ascii


namespace nonstd::string_utils
{


// The following functions are not Unicode aware and simply do byte comparisons
//

inline bool starts_with(std::string_view sv, std::string_view test)
{
  if (sv.empty() || test.empty() || test.size() > sv.size())
    return false;
  return detail::compare(std::begin(sv), std::begin(test), std::end(test));
}


inline bool ends_with(std::string_view sv, std::string_view test)
{
  if (sv.empty() || test.empty() || test.size() > sv.size())
    return false;
  return detail::compare(std::rbegin(sv), std::rbegin(test), std::rend(test));
}


inline std::vector<std::string_view> split(std::string_view sv, std::string_view token,
    bool keep_empty_parts = true)
{
  if (keep_empty_parts)
    return detail::split_keep_empty<std::string_view>(sv, token);
  return detail::split_ignore_empty<std::string_view>(sv, token);
}


inline std::vector<std::string> split_copy(std::string_view sv, std::string_view token,
    bool keep_empty_parts = true)
{
  if (keep_empty_parts)
    return detail::split_keep_empty<std::string>(sv, token);
  return detail::split_ignore_empty<std::string>(sv, token);
}


inline std::tuple<std::string_view, std::string_view> split_first(std::string_view sv,
    std::string_view token)
{
  return detail::split_first<std::string_view>(sv, token);
}


inline std::tuple<std::string, std::string> split_first_copy(std::string_view sv,
    std::string_view token)
{
  return detail::split_first<std::string>(sv, token);
}


inline std::tuple<std::string_view, std::string_view> split_last(std::string_view sv,
    std::string_view token)
{
  return detail::split_last<std::string_view>(sv, token);
}


inline std::tuple<std::string, std::string> split_last_copy(std::string_view sv,
    std::string_view token)
{
  return detail::split_last<std::string>(sv, token);
}


inline std::string_view before_first(std::string_view sv, std::string_view token)
{
  return detail::before_first<std::string_view>(sv, token);
}


inline std::string before_first_copy(std::string_view sv, std::string_view token)
{
  return detail::before_first<std::string>(sv, token);
}


inline std::string_view before_last(std::string_view sv, std::string_view token)
{
  return detail::before_last<std::string_view>(sv, token);
}


inline std::string before_last_copy(std::string_view sv, std::string_view token)
{
  return detail::before_last<std::string>(sv, token);
}


inline std::string_view after_first(std::string_view sv, std::string_view token)
{
  return detail::after_first<std::string_view>(sv, token);
}


inline std::string after_first_copy(std::string_view sv, std::string_view token)
{
  return detail::after_first<std::string>(sv, token);
}


inline std::string_view after_last(std::string_view sv, std::string_view token)
{
  return detail::after_last<std::string_view>(sv, token);
}


inline std::string after_last_copy(std::string_view sv, std::string_view token)
{
  return detail::after_last<std::string>(sv, token);
}


inline std::string_view between(std::string_view sv, std::string_view first_token,
    std::string_view second_token, bool greedy = false)
{
  return detail::between<std::string_view>(sv, first_token, second_token, greedy);
}


inline std::string between_copy(std::string_view sv, std::string_view first_token,
    std::string_view second_token, bool greedy = false)
{
  return detail::between<std::string>(sv, first_token, second_token, greedy);
}


inline std::string_view rbetween(std::string_view sv, std::string_view first_token,
    std::string_view second_token, bool greedy = false)
{
  return detail::rbetween<std::string_view>(sv, first_token, second_token, greedy);
}


inline std::string rbetween_copy(std::string_view sv, std::string_view first_token,
    std::string_view second_token, bool greedy = false)
{
  return detail::rbetween<std::string>(sv, first_token, second_token, greedy);
}


inline std::string replace(std::string_view sv, std::string_view search_token,
    std::string_view replace_token)
{
  if (search_token.size() == replace_token.size())
    return detail::replace_inplace(sv, search_token, replace_token);
  return detail::replace(sv, search_token, replace_token);
}


#ifdef NONSTD_STRING_UTILS_CHARCONV
  inline std::string as_string(std::string_view sv)
  {
    return std::string{sv};
  }


  inline int as_int(std::string_view sv, int base = 10)
  {
    return detail::parse_number<int>(sv, base);
  }


  inline std::uint8_t as_uint8(std::string_view sv, int base = 10)
  {
    return detail::parse_number<std::uint8_t>(sv, base);
  }


  inline std::uint16_t as_uint16(std::string_view sv, int base = 10)
  {
    return detail::parse_number<std::uint16_t>(sv, base);
  }


  inline std::uint32_t as_uint32(std::string_view sv, int base = 10)
  {
    return detail::parse_number<std::uint32_t>(sv, base);
  }


  inline std::uint64_t as_uint64(std::string_view sv, int base = 10)
  {
    return detail::parse_number<std::uint64_t>(sv, base);
  }


  inline std::int8_t as_int8(std::string_view sv, int base = 10)
  {
    return detail::parse_number<std::int8_t>(sv, base);
  }


  inline std::int16_t as_int16(std::string_view sv, int base = 10)
  {
    return detail::parse_number<std::int16_t>(sv, base);
  }


  inline std::int32_t as_int32(std::string_view sv, int base = 10)
  {
    return detail::parse_number<std::int32_t>(sv, base);
  }


  inline std::int64_t as_int64(std::string_view sv, int base = 10)
  {
    return detail::parse_number<std::int64_t>(sv, base);
  }

  
  #ifdef NONSTD_STRING_UTILS_CHARCONV_INTEGRAL_TYPES_ONLY
    inline float as_float(std::string_view sv)
    {
      return std::stof(std::string{sv});
    }


    inline double as_double(std::string_view sv)
    {
      return std::stod(std::string{sv});
    }


    inline long double as_longdouble(std::string_view sv)
    {
      return std::stold(std::string{sv});
    }
  #else
    inline float as_float(std::string_view sv)
    {
      return detail::parse_number<float>(sv);
    }


    inline double as_double(std::string_view sv)
    {
      return detail::parse_number<double>(sv);
    }


    inline long double as_longdouble(std::string_view sv)
    {
      return detail::parse_number<long double>(sv);
    }
  #endif
#endif  // NONSTD_STRING_UTILS_CHARCONV


}  // namespace nonstd::string_utils


#endif  // NONSTD_STRING_UTILS_H