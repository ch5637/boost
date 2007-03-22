/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_TAG_OF_09232005_0845)
#define FUSION_TAG_OF_09232005_0845

#include <boost/type_traits/remove_const.hpp>
#include <boost/fusion/support/tag_of_fwd.hpp>
#include <boost/fusion/support/detail/is_mpl_sequence.hpp>
#include <boost/mpl/has_xxx.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <utility>

namespace boost
{
    template <typename T, std::size_t N>
    class array; // forward

    namespace tuples
    {
        struct null_type;
        
        template <
            class T0, class T1, class T2, class T3, class T4, 
            class T5, class T6, class T7, class T8, class T9
        >
        class tuple;
    
        template <class Head, class Tail>
        struct cons;
    }
}

namespace boost { namespace fusion
{
    struct non_fusion_tag;
    struct mpl_sequence_tag;

    namespace detail
    {
        BOOST_MPL_HAS_XXX_TRAIT_DEF(fusion_tag)
    }

    namespace traits
    {
        template <typename Sequence, typename Active>
        struct tag_of
          : mpl::if_< detail::is_mpl_sequence<Sequence>,
              mpl::identity<mpl_sequence_tag>,
              mpl::identity<non_fusion_tag> >::type
        { };

        template <typename Sequence>
        struct tag_of<Sequence, typename boost::enable_if<detail::has_fusion_tag<Sequence> >::type>
        {
            typedef typename Sequence::fusion_tag type;
        };

        template <
            class T0, class T1, class T2, class T3, class T4, 
            class T5, class T6, class T7, class T8, class T9
        >
        struct tag_of<tuples::tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> >;

        template <class Head, class Tail>
        struct tag_of<tuples::cons<Head, Tail> >;

        template <>
        struct tag_of<tuples::null_type>;

        template <typename T, std::size_t N>
        struct tag_of<boost::array<T, N> >;

        template<typename T1, typename T2>
        struct tag_of<std::pair<T1, T2> >;
    }

    namespace detail
    {
        template<typename T>
        struct tag_of
            : traits::tag_of<typename remove_const<T>::type>
        {};
    }
}}
#endif
