#ifndef SKELETONS_SEQ_HPP
#define SKELETONS_SEQ_HPP

#include <hpx/include/iostreams.hpp>
#include <vector>
#include <cstdint>

#include <boost/format.hpp>

#include "API.hpp"
#include "util/NodeGenerator.hpp"
#include "util/Enumerator.hpp"
#include "util/func.hpp"

namespace YewPar { namespace Skeletons {

template <typename Generator, typename ...Args>
struct Seq {
  typedef typename Generator::Nodetype Node;
  typedef typename Generator::Spacetype Space;

  typedef typename API::skeleton_signature::bind<Args...>::type args;

  static constexpr bool isEnumeration = parameter::value_type<args, API::tag::Enumeration_, std::integral_constant<bool, false> >::type::value;
  static constexpr bool isBnB = parameter::value_type<args, API::tag::Optimisation_, std::integral_constant<bool, false> >::type::value;
  static constexpr bool isDecision = parameter::value_type<args, API::tag::Decision_, std::integral_constant<bool, false> >::type::value;
  static constexpr bool isDepthBounded = parameter::value_type<args, API::tag::DepthLimited_, std::integral_constant<bool, false> >::type::value;
  static constexpr bool pruneLevel = parameter::value_type<args, API::tag::PruneLevel_, std::integral_constant<bool, false> >::type::value;
  static constexpr unsigned verbose = parameter::value_type<args, API::tag::Verbose_, std::integral_constant<unsigned, 0> >::type::value;
  typedef typename parameter::value_type<args, API::tag::BoundFunction, nullFn__>::type boundFn;
  typedef typename boundFn::return_type Bound;
  typedef typename parameter::value_type<args, API::tag::ObjectiveComparison, std::greater<Bound> >::type Objcmp;
  typedef typename parameter::value_type<args, API::tag::Enumerator, IdentityEnumerator<Node>>::type Enumerator;

  static void printSkeletonDetails() {
    hpx::cout << "Skeleton Type: Seq\n";
    hpx::cout << "Enumeration: " << std::boolalpha << isEnumeration << "\n";
    hpx::cout << "Optimisation: " << std::boolalpha << isBnB << "\n";
    hpx::cout << "Decision: " << std::boolalpha << isDecision << "\n";
    hpx::cout << "DepthBounded: " << std::boolalpha << isDepthBounded << "\n";
      hpx::cout << "Using Bounding: false\n";
    hpx::cout << hpx::flush;
  }

  static bool expand(const Space & space,
                     const Node & n,
                     const API::Params<Bound> & params,
                     std::pair<Node, Bound> & incumbent,
                     const unsigned childDepth,
                     Enumerator & acc) {
    Generator newCands = Generator(space, n);

    if (1) {
        acc.accumulate(n);
    }

    if (1) {
        if (childDepth == params.maxDepth) {
          return false;
        }
    }

    for (auto i = 0; i < newCands.numChildren; ++i) {
      auto c = newCands.next();

      // Do we support bounding?
      if (1) {
          Objcmp cmp;
          auto bnd  = boundFn::invoke(space, c);
          if (1) {
            auto best = std::get<1>(incumbent);
            if (!cmp(bnd,best)) {
              continue;
            }
          }
      }

      auto found = expand(space, c, params, incumbent, childDepth + 1, acc);
    }
    return false;
  }

  static auto search (const Space & space,
                      const Node & root,
                      const API::Params<Bound> params = API::Params<Bound>()) {
    static_assert(isEnumeration || isBnB || isDecision, "Please provide a supported search type: Enumeration, BnB, Decision");

      printSkeletonDetails();

    Enumerator acc;

    std::pair<Node, Bound> incumbent = std::make_pair(root, params.initialBound);
    expand(space, root, params, incumbent, 1, acc);

      return std::get<0>(incumbent);
  }

  static auto findsearch (const Space & space,
                      const Node & root,
                      const API::Params<Bound> params = API::Params<Bound>()) {
    static_assert(isEnumeration || isBnB || isDecision, "Please provide a supported search type: Enumeration, BnB, Decision");

      printSkeletonDetails();

    Enumerator acc;

    std::pair<Node, Bound> incumbent = std::make_pair(root, params.initialBound);
    expand(space, root, params, incumbent, 1, acc);

      return acc.get();
  }
};


}}

#endif
