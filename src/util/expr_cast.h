/*******************************************************************\

Module:

Author: Nathan Phillips <Nathan.Phillips@diffblue.com>

\*******************************************************************/

#ifndef CPROVER_UTIL_EXPR_CAST_H
#define CPROVER_UTIL_EXPR_CAST_H

/// \file util/expr_cast.h
/// \brief Templated functions to cast to specific exprt-derived classes

#include <typeinfo>
#include <type_traits>
#include <functional>

#include "invariant.h"
#include "expr.h"
#include "optional.h"

/// \brief Check whether a reference to a generic \ref exprt is of a specific
///   derived class.
///
///   Implement template specializations of this function to enable casting
///
/// \tparam T The exprt-derived class to check for
/// \param base Reference to a generic \ref exprt
/// \return true if \a base is of type \a T
template<typename T> bool can_cast_expr(const exprt &base);


/// \brief Try to cast a constant reference to a generic exprt to a specific
///   derived class
/// \tparam T The exprt-derived class to cast to
/// \param base Reference to a generic \ref exprt
/// \return Reference to object of type \a T or valueless optional if \a base
///   is not an instance of \a T
template<typename T>
optionalt<std::reference_wrapper<typename std::remove_reference<T>::type>>
expr_try_dynamic_cast(const exprt &base)
{
  return expr_try_dynamic_cast<
    T,
    typename std::remove_reference<T>::type,
    typename std::remove_const<typename std::remove_reference<T>::type>::type,
    const exprt>(base);
}

/// \brief Try to cast a reference to a generic exprt to a specific derived
///   class
/// \tparam T The exprt-derived class to cast to
/// \param base Reference to a generic \ref exprt
/// \return Reference to object of type \a T or valueless optional if \a base is
///   not an instance of \a T
template<typename T>
optionalt<std::reference_wrapper<typename std::remove_reference<T>::type>>
expr_try_dynamic_cast(exprt &base)
{
  return expr_try_dynamic_cast<
    T,
    typename std::remove_reference<T>::type,
    typename std::remove_const<typename std::remove_reference<T>::type>::type,
    exprt>(base);
}

/// \brief Try to cast a reference to a generic exprt to a specific derived
///    class
/// \tparam T The reference or const reference type to \a TUnderlying to cast
///    to
/// \tparam TUnderlying An exprt-derived class type
/// \tparam TExpr The original type to cast from, either exprt or const exprt
/// \param base Reference to a generic \ref exprt
/// \return Reference to object of type \a TUnderlying
///   or valueless optional if \a base is not an instance of \a TUnderlying
template<typename T, typename TConst, typename TUnderlying, typename TExpr>
optionalt<std::reference_wrapper<TConst>> expr_try_dynamic_cast(TExpr &base)
{
  static_assert(
    std::is_same<typename std::remove_const<TExpr>::type, exprt>::value,
    "Tried to expr_try_dynamic_cast from something that wasn't an exprt");
  static_assert(
    std::is_reference<T>::value,
    "Tried to convert exprt & to non-reference type");
  static_assert(
    std::is_base_of<exprt, TUnderlying>::value,
    "The template argument T must be derived from exprt.");
  if(!can_cast_expr<TUnderlying>(base))
    return optionalt<std::reference_wrapper<TConst>>();
  T value=static_cast<T>(base);
  validate_expr(value);
  return optionalt<std::reference_wrapper<TConst>>(value);
}

/// \brief Cast a constant reference to a generic exprt to a specific derived
///   class
/// \tparam T The exprt-derived class to cast to
/// \param base Reference to a generic \ref exprt
/// \return Reference to object of type \a T
/// \throw std::bad_cast If \a base is not an instance of \a T
/// \remark If CBMC assertions (PRECONDITION) are set to abort then this will
///   abort rather than throw if \a base is not an instance of \a T
template<typename T>
T expr_dynamic_cast(const exprt &base)
{
  return expr_dynamic_cast<
    T,
    typename std::remove_const<typename std::remove_reference<T>::type>::type,
    const exprt>(base);
}

/// \brief Cast a reference to a generic exprt to a specific derived class
/// \tparam T The exprt-derived class to cast to
/// \param base Reference to a generic \ref exprt
/// \return Reference to object of type \a T
/// \throw std::bad_cast If \a base is not an instance of \a T
/// \remark If CBMC assertions (PRECONDITION) are set to abort then this will
///   abort rather than throw if \a base is not an instance of \a T
template<typename T>
T expr_dynamic_cast(exprt &base)
{
  return expr_dynamic_cast<
    T,
    typename std::remove_const<typename std::remove_reference<T>::type>::type,
    exprt>(base);
}

/// \brief Cast a reference to a generic exprt to a specific derived class
/// \tparam T The reference or const reference type to \a TUnderlying to cast to
/// \tparam TUnderlying An exprt-derived class type
/// \tparam TExpr The original type to cast from, either exprt or const exprt
/// \param base Reference to a generic \ref exprt
/// \return Reference to object of type \a T
/// \throw std::bad_cast If \a base is not an instance of \a TUnderlying
/// \remark If CBMC assertions (PRECONDITION) are set to abort then this will
///   abort rather than throw if \a base is not an instance of \a TUnderlying
template<typename T, typename TUnderlying, typename TExpr>
T expr_dynamic_cast(TExpr &base)
{
  static_assert(
    std::is_same<typename std::remove_const<TExpr>::type, exprt>::value,
    "Tried to expr_dynamic_cast from something that wasn't an exprt");
  static_assert(
    std::is_reference<T>::value,
    "Tried to convert exprt & to non-reference type");
  static_assert(
    std::is_base_of<exprt, TUnderlying>::value,
    "The template argument T must be derived from exprt.");
  PRECONDITION(can_cast_expr<TUnderlying>(base));
  if(!can_cast_expr<TUnderlying>(base))
    throw std::bad_cast();
  T value=static_cast<T>(base);
  validate_expr(value);
  return value;
}


inline void validate_operands(
  const exprt &value,
  exprt::operandst::size_type number,
  const char *message,
  bool allow_more=false)
{
  DATA_INVARIANT(
    allow_more
      ? value.operands().size()==number
      : value.operands().size()>=number,
    message);
}

#endif  // CPROVER_UTIL_EXPR_CAST_H
