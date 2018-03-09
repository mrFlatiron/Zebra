#ifndef WORK_TEMPLATE_UTILS_H
#define WORK_TEMPLATE_UTILS_H

#include <type_traits>
#include <utility>
#include <iomanip>
#include <sstream>

namespace work
{ 
  template<typename T, typename Ref = std::add_lvalue_reference_t<T>>
    Ref declref_helper (int);

  template<typename T>
    T declref_helper (long);

  template<typename T>
    auto declref () noexcept -> decltype (declref_helper<T> (0));


    template<typename T>
    using use_if_primitive = std::enable_if_t<std::is_fundamental_v<T>
                                              || std::is_enum_v<T>
                                              || std::is_convertible_v<T, std::string>,void>;

    template<typename T>
    struct is_primitive
    {
    private:
      template<typename C, typename = use_if_primitive<T>>
      constexpr bool is_primitive_impl (int) {return true;}

      template<typename C>
      constexpr bool is_primitive_impl (char) {return false;}
    public:
      static constexpr bool value = is_primitive_impl<T> (0);

    };

    template<typename T>
    inline constexpr bool is_primitive_v = is_primitive<T>::value;

    template<size_t Priority>
    struct priority_tag : public priority_tag<Priority - 1> {};

    template<>
    struct priority_tag<0> {};

    template<typename T, typename... Args>
    void put_in (std::unique_ptr<T> &something, Args&&... args)
    {
      something = std::make_unique<T> (std::forward<Args> (args)...);
    }

    template<typename T>
    T from_string (std::string_view str)
    {
      if constexpr (std::is_same_v<T, double>)
      {
        return strtod (str.data (), nullptr);
      }
      if constexpr (std::is_same_v<T, float>)
      {
        return strtof (str.data (), nullptr);
      }
      if constexpr (std::is_same_v<T, long double>)
      {
        return strtold (str.data (), nullptr);
      }
      if constexpr (std::is_same_v<T, int>)
      {
        return strtol (str.data (), nullptr, 10);
      }
      if constexpr (std::is_same_v<T, long>)
      {
        return strtol (str.data (), nullptr, 10);
      }
      if constexpr (std::is_same_v<T, unsigned long>)
      {
        return strtoul (str.data (), nullptr, 10);
      }
      if constexpr (std::is_same_v<T, long long>)
      {
        return strtoll (str.data (), nullptr, 10);
      }
      if constexpr (std::is_same_v<T, unsigned long long>)
      {
        return strtoull (str.data (), nullptr, 10);
      }
    }

    template<typename T>
    std::string to_string_enh (const T &obj)
    {
      if constexpr (std::is_same_v<T, double>)
      {
        std::stringstream stream;
        stream << std::setprecision (std::numeric_limits<long double>::digits10 + 1) << obj;
        return stream.str ();
      }

      return std::to_string (obj);
    }
}

#endif // WORK_TEMPLATE_UTILS_H
