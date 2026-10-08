# Results on test directory

| file | cpp generate | cpp compilation | run | result diff |
| ---- | ------------ | --------------- | --- | ----------- |
| [HelloWorld.go](tests/HelloWorld.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/HelloWorld.cpp)) | ❌ |
| [TourOfGo/basics/basic-types.go](tests/TourOfGo/basics/basic-types.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/basics/basic-types.cpp)) | ❌ |
| [TourOfGo/basics/constants.go](tests/TourOfGo/basics/constants.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/basics/constants.cpp)) | ✔️ |
| [TourOfGo/basics/ellipsis.go](tests/TourOfGo/basics/ellipsis.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/basics/ellipsis.cpp)) | ✔️ |
| [TourOfGo/basics/exported-names.go](tests/TourOfGo/basics/exported-names.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/basics/exported-names.cpp)) | ✔️ |
| [TourOfGo/basics/functions.go](tests/TourOfGo/basics/functions.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/basics/functions.cpp)) | ✔️ |
| [TourOfGo/basics/functions-continued.go](tests/TourOfGo/basics/functions-continued.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/basics/functions-continued.cpp)) | ✔️ |
| [TourOfGo/basics/imports.go](tests/TourOfGo/basics/imports.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/basics/imports.cpp)) | ❌ |
| [TourOfGo/basics/inline-values.go](tests/TourOfGo/basics/inline-values.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/basics/inline-values.cpp)) | ✔️ |
| [TourOfGo/basics/iota.go](tests/TourOfGo/basics/iota.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/basics/iota.cpp)) | ✔️ |
| [TourOfGo/basics/multiple-results.go](tests/TourOfGo/basics/multiple-results.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/basics/multiple-results.cpp)) | ✔️ |
| [TourOfGo/basics/name-conflicts.go](tests/TourOfGo/basics/name-conflicts.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/basics/name-conflicts.cpp)) | ✔️ |
| [TourOfGo/basics/name-conflicts-full.go](tests/TourOfGo/basics/name-conflicts-full.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/basics/name-conflicts-full.cpp)) | ✔️ |
| [TourOfGo/basics/named-results.go](tests/TourOfGo/basics/named-results.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/basics/named-results.cpp)) | ❌ |
| [TourOfGo/basics/numeric-constants.go](tests/TourOfGo/basics/numeric-constants.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/basics/numeric-constants.cpp)) | ❌ |
| [TourOfGo/basics/packages.go](tests/TourOfGo/basics/packages.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/basics/packages.cpp)) | ➖ | 
| [TourOfGo/basics/panic-recover.go](tests/TourOfGo/basics/panic-recover.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/basics/panic-recover.cpp)) | ✔️ |
| [TourOfGo/basics/short-variable-declarations.go](tests/TourOfGo/basics/short-variable-declarations.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/basics/short-variable-declarations.cpp)) | ✔️ |
| [TourOfGo/basics/type-conversions.go](tests/TourOfGo/basics/type-conversions.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/basics/type-conversions.cpp)) | ✔️ |
| [TourOfGo/basics/type-conversions-advanced.go](tests/TourOfGo/basics/type-conversions-advanced.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/basics/type-conversions-advanced.cpp)) | ❌ |
| [TourOfGo/basics/type-inference.go](tests/TourOfGo/basics/type-inference.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/basics/type-inference.cpp)) | ❌ |
| [TourOfGo/basics/variables.go](tests/TourOfGo/basics/variables.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/basics/variables.cpp)) | ✔️ |
| [TourOfGo/basics/variables-mixed-declaration.go](tests/TourOfGo/basics/variables-mixed-declaration.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/basics/variables-mixed-declaration.cpp)) | ✔️ |
| [TourOfGo/basics/variables-with-initializers.go](tests/TourOfGo/basics/variables-with-initializers.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/basics/variables-with-initializers.cpp)) | ✔️ |
| [TourOfGo/basics/zero.go](tests/TourOfGo/basics/zero.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/basics/zero.cpp)) | ❌ |
| [TourOfGo/concurrency/buffered-channels.go](tests/TourOfGo/concurrency/buffered-channels.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/concurrency/buffered-channels.cpp)) | ✔️ |
| [TourOfGo/concurrency/channels.go](tests/TourOfGo/concurrency/channels.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/concurrency/channels.cpp)) | ✔️ |
| [TourOfGo/concurrency/channels-opt.go](tests/TourOfGo/concurrency/channels-opt.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/concurrency/channels-opt.cpp)) | ✔️ |
| [TourOfGo/concurrency/default-selection.go](tests/TourOfGo/concurrency/default-selection.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/concurrency/default-selection.cpp)) | ❌ |
| [TourOfGo/concurrency/exercise-equivalent-binary-trees.go](tests/TourOfGo/concurrency/exercise-equivalent-binary-trees.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/concurrency/exercise-equivalent-binary-trees.cpp)) | ❌ |
| [TourOfGo/concurrency/exercise-web-crawler.go](tests/TourOfGo/concurrency/exercise-web-crawler.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/concurrency/exercise-web-crawler.cpp)) | ❌ |
| [TourOfGo/concurrency/goroutines.go](tests/TourOfGo/concurrency/goroutines.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/concurrency/goroutines.cpp)) | ✔️ |
| [TourOfGo/concurrency/mutex-counter.go](tests/TourOfGo/concurrency/mutex-counter.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/concurrency/mutex-counter.cpp)) | ✔️ |
| [TourOfGo/concurrency/mutex-counter-ptr.go](tests/TourOfGo/concurrency/mutex-counter-ptr.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/concurrency/mutex-counter-ptr.cpp)) | ✔️ |
| [TourOfGo/concurrency/range-and-close.go](tests/TourOfGo/concurrency/range-and-close.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/concurrency/range-and-close.cpp)) | ✔️ |
| [TourOfGo/concurrency/select.go](tests/TourOfGo/concurrency/select.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/concurrency/select.cpp)) | ✔️ |
| [TourOfGo/flowcontrol/defer.go](tests/TourOfGo/flowcontrol/defer.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/flowcontrol/defer.cpp)) | ✔️ |
| [TourOfGo/flowcontrol/defer-multi.go](tests/TourOfGo/flowcontrol/defer-multi.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/flowcontrol/defer-multi.cpp)) | ✔️ |
| [TourOfGo/flowcontrol/exercise-loops-and-functions.go](tests/TourOfGo/flowcontrol/exercise-loops-and-functions.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/flowcontrol/exercise-loops-and-functions.cpp)) | ✔️ |
| [TourOfGo/flowcontrol/for.go](tests/TourOfGo/flowcontrol/for.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/flowcontrol/for.cpp)) | ✔️ |
| [TourOfGo/flowcontrol/for-break-continue.go](tests/TourOfGo/flowcontrol/for-break-continue.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/flowcontrol/for-break-continue.cpp)) | ✔️ |
| [TourOfGo/flowcontrol/for-continued.go](tests/TourOfGo/flowcontrol/for-continued.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/flowcontrol/for-continued.cpp)) | ✔️ |
| [TourOfGo/flowcontrol/forever.go](tests/TourOfGo/flowcontrol/forever.go) | ✔️ | ✔️ | ➖ | ➖ | 
| [TourOfGo/flowcontrol/for-is-gos-while.go](tests/TourOfGo/flowcontrol/for-is-gos-while.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/flowcontrol/for-is-gos-while.cpp)) | ✔️ |
| [TourOfGo/flowcontrol/if.go](tests/TourOfGo/flowcontrol/if.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/flowcontrol/if.cpp)) | ❌ |
| [TourOfGo/flowcontrol/if-and-else.go](tests/TourOfGo/flowcontrol/if-and-else.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/flowcontrol/if-and-else.cpp)) | ❌ |
| [TourOfGo/flowcontrol/if-with-a-short-statement.go](tests/TourOfGo/flowcontrol/if-with-a-short-statement.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/flowcontrol/if-with-a-short-statement.cpp)) | ✔️ |
| [TourOfGo/flowcontrol/inlined-statements-scope.go](tests/TourOfGo/flowcontrol/inlined-statements-scope.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/flowcontrol/inlined-statements-scope.cpp)) | ✔️ |
| [TourOfGo/flowcontrol/labels.go](tests/TourOfGo/flowcontrol/labels.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/flowcontrol/labels.cpp)) | ✔️ |
| [TourOfGo/flowcontrol/switch.go](tests/TourOfGo/flowcontrol/switch.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/flowcontrol/switch.cpp)) | ❌ |
| [TourOfGo/flowcontrol/switch-evaluation-order.go](tests/TourOfGo/flowcontrol/switch-evaluation-order.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/flowcontrol/switch-evaluation-order.cpp)) | ➖ | 
| [TourOfGo/flowcontrol/switch-numeric.go](tests/TourOfGo/flowcontrol/switch-numeric.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/flowcontrol/switch-numeric.cpp)) | ➖ | 
| [TourOfGo/flowcontrol/switch-with-no-condition.go](tests/TourOfGo/flowcontrol/switch-with-no-condition.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/flowcontrol/switch-with-no-condition.cpp)) | ➖ | 
| [TourOfGo/generics/generics.go](tests/TourOfGo/generics/generics.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/generics/generics.cpp)) | ✔️ |
| [TourOfGo/libs/hex.go](tests/TourOfGo/libs/hex.go) | ✔️ | ❌ | ❌ | ❌ |
| [TourOfGo/methods/empty-interface.go](tests/TourOfGo/methods/empty-interface.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/methods/empty-interface.cpp)) | ❌ |
| [TourOfGo/methods/errors.go](tests/TourOfGo/methods/errors.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/methods/errors.cpp)) | ❌ |
| [TourOfGo/methods/exercise-errors.go](tests/TourOfGo/methods/exercise-errors.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/methods/exercise-errors.cpp)) | ❌ |
| [TourOfGo/methods/exercise-images.go](tests/TourOfGo/methods/exercise-images.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/methods/exercise-images.cpp)) | ❌ |
| [TourOfGo/methods/exercise-reader.go](tests/TourOfGo/methods/exercise-reader.go) | ✔️ | ❌ | ❌ | ❌ |
| [TourOfGo/methods/exercise-rot-reader.go](tests/TourOfGo/methods/exercise-rot-reader.go) | ✔️ | ❌ | ❌ | ❌ |
| [TourOfGo/methods/exercise-stringer.go](tests/TourOfGo/methods/exercise-stringer.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/methods/exercise-stringer.cpp)) | ❌ |
| [TourOfGo/methods/images.go](tests/TourOfGo/methods/images.go) | ✔️ | ❌ | ❌ | ❌ |
| [TourOfGo/methods/indirection.go](tests/TourOfGo/methods/indirection.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/methods/indirection.cpp)) | ✔️ |
| [TourOfGo/methods/indirection-values.go](tests/TourOfGo/methods/indirection-values.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/methods/indirection-values.cpp)) | ✔️ |
| [TourOfGo/methods/inline-interface.go](tests/TourOfGo/methods/inline-interface.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/methods/inline-interface.cpp)) | ❌ |
| [TourOfGo/methods/interfaces.go](tests/TourOfGo/methods/interfaces.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/methods/interfaces.cpp)) | ✔️ |
| [TourOfGo/methods/interfaces-are-satisfied-implicitly.go](tests/TourOfGo/methods/interfaces-are-satisfied-implicitly.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/methods/interfaces-are-satisfied-implicitly.cpp)) | ✔️ |
| [TourOfGo/methods/interfaces-cast.go](tests/TourOfGo/methods/interfaces-cast.go) | ✔️ | ✔️ | ❌ | ❌ |
| [TourOfGo/methods/interfaces-ordered.go](tests/TourOfGo/methods/interfaces-ordered.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/methods/interfaces-ordered.cpp)) | ✔️ |
| [TourOfGo/methods/interface-values.go](tests/TourOfGo/methods/interface-values.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/methods/interface-values.cpp)) | ❌ |
| [TourOfGo/methods/interface-values-with-nil.go](tests/TourOfGo/methods/interface-values-with-nil.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/methods/interface-values-with-nil.cpp)) | ❌ |
| [TourOfGo/methods/interface-values-with-unitialized.go](tests/TourOfGo/methods/interface-values-with-unitialized.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/methods/interface-values-with-unitialized.cpp)) | ❌ |
| [TourOfGo/methods/methods.go](tests/TourOfGo/methods/methods.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/methods/methods.cpp)) | ✔️ |
| [TourOfGo/methods/methods-continued.go](tests/TourOfGo/methods/methods-continued.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/methods/methods-continued.cpp)) | ✔️ |
| [TourOfGo/methods/methods-funcs.go](tests/TourOfGo/methods/methods-funcs.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/methods/methods-funcs.cpp)) | ✔️ |
| [TourOfGo/methods/methods-pointers.go](tests/TourOfGo/methods/methods-pointers.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/methods/methods-pointers.cpp)) | ✔️ |
| [TourOfGo/methods/methods-pointers-explained.go](tests/TourOfGo/methods/methods-pointers-explained.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/methods/methods-pointers-explained.cpp)) | ✔️ |
| [TourOfGo/methods/methods-with-pointer-receivers.go](tests/TourOfGo/methods/methods-with-pointer-receivers.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/methods/methods-with-pointer-receivers.cpp)) | ❌ |
| [TourOfGo/methods/nil-interface-values.go](tests/TourOfGo/methods/nil-interface-values.go) | ✔️ | ✔️ | ➖ | ➖ | 
| [TourOfGo/methods/reader.go](tests/TourOfGo/methods/reader.go) | ✔️ | ❌ | ❌ | ❌ |
| [TourOfGo/methods/stringer.go](tests/TourOfGo/methods/stringer.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/methods/stringer.cpp)) | ❌ |
| [TourOfGo/methods/type-assertions.go](tests/TourOfGo/methods/type-assertions.go) | ✔️ | ❌ | ❌ | ❌ |
| [TourOfGo/methods/type-assertions-basics.go](tests/TourOfGo/methods/type-assertions-basics.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/methods/type-assertions-basics.cpp)) | ✔️ |
| [TourOfGo/methods/type-switches.go](tests/TourOfGo/methods/type-switches.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/methods/type-switches.cpp)) | ❌ |
| [TourOfGo/moretypes/append.go](tests/TourOfGo/moretypes/append.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/moretypes/append.cpp)) | ❌ |
| [TourOfGo/moretypes/array.go](tests/TourOfGo/moretypes/array.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/moretypes/array.cpp)) | ✔️ |
| [TourOfGo/moretypes/exercise-fibonacci-closure.go](tests/TourOfGo/moretypes/exercise-fibonacci-closure.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/moretypes/exercise-fibonacci-closure.cpp)) | ✔️ |
| [TourOfGo/moretypes/exercise-maps.go](tests/TourOfGo/moretypes/exercise-maps.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/moretypes/exercise-maps.cpp)) | ✔️ |
| [TourOfGo/moretypes/exercise-slices.go](tests/TourOfGo/moretypes/exercise-slices.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/moretypes/exercise-slices.cpp)) | ❌ |
| [TourOfGo/moretypes/function-closures.go](tests/TourOfGo/moretypes/function-closures.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/moretypes/function-closures.cpp)) | ✔️ |
| [TourOfGo/moretypes/function-values.go](tests/TourOfGo/moretypes/function-values.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/moretypes/function-values.cpp)) | ✔️ |
| [TourOfGo/moretypes/making-slices.go](tests/TourOfGo/moretypes/making-slices.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/moretypes/making-slices.cpp)) | ❌ |
| [TourOfGo/moretypes/map-literals.go](tests/TourOfGo/moretypes/map-literals.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/moretypes/map-literals.cpp)) | ✔️ |
| [TourOfGo/moretypes/map-literals-continued.go](tests/TourOfGo/moretypes/map-literals-continued.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/moretypes/map-literals-continued.cpp)) | ✔️ |
| [TourOfGo/moretypes/maps.go](tests/TourOfGo/moretypes/maps.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/moretypes/maps.cpp)) | ✔️ |
| [TourOfGo/moretypes/mutating-maps.go](tests/TourOfGo/moretypes/mutating-maps.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/moretypes/mutating-maps.cpp)) | ❌ |
| [TourOfGo/moretypes/nil-slices.go](tests/TourOfGo/moretypes/nil-slices.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/moretypes/nil-slices.cpp)) | ✔️ |
| [TourOfGo/moretypes/pointers.go](tests/TourOfGo/moretypes/pointers.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/moretypes/pointers.cpp)) | ✔️ |
| [TourOfGo/moretypes/range.go](tests/TourOfGo/moretypes/range.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/moretypes/range.cpp)) | ✔️ |
| [TourOfGo/moretypes/range-continued.go](tests/TourOfGo/moretypes/range-continued.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/moretypes/range-continued.cpp)) | ✔️ |
| [TourOfGo/moretypes/slice-bounds.go](tests/TourOfGo/moretypes/slice-bounds.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/moretypes/slice-bounds.cpp)) | ✔️ |
| [TourOfGo/moretypes/slice-len-cap.go](tests/TourOfGo/moretypes/slice-len-cap.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/moretypes/slice-len-cap.cpp)) | ❌ |
| [TourOfGo/moretypes/slice-literals.go](tests/TourOfGo/moretypes/slice-literals.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/moretypes/slice-literals.cpp)) | ✔️ |
| [TourOfGo/moretypes/slices.go](tests/TourOfGo/moretypes/slices.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/moretypes/slices.cpp)) | ✔️ |
| [TourOfGo/moretypes/slices-of-slice.go](tests/TourOfGo/moretypes/slices-of-slice.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/moretypes/slices-of-slice.cpp)) | ✔️ |
| [TourOfGo/moretypes/slices-pointers.go](tests/TourOfGo/moretypes/slices-pointers.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/moretypes/slices-pointers.cpp)) | ✔️ |
| [TourOfGo/moretypes/struct-fields.go](tests/TourOfGo/moretypes/struct-fields.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/moretypes/struct-fields.cpp)) | ✔️ |
| [TourOfGo/moretypes/struct-fields-initializer.go](tests/TourOfGo/moretypes/struct-fields-initializer.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/moretypes/struct-fields-initializer.cpp)) | ✔️ |
| [TourOfGo/moretypes/struct-literals.go](tests/TourOfGo/moretypes/struct-literals.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/moretypes/struct-literals.cpp)) | ✔️ |
| [TourOfGo/moretypes/struct-pointers.go](tests/TourOfGo/moretypes/struct-pointers.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/moretypes/struct-pointers.cpp)) | ✔️ |
| [TourOfGo/moretypes/structs.go](tests/TourOfGo/moretypes/structs.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/moretypes/structs.cpp)) | ✔️ |
| [TourOfGo/moretypes/structs-interface.go](tests/TourOfGo/moretypes/structs-interface.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/moretypes/structs-interface.cpp)) | ❌ |
| [TourOfGo/moretypes/typedef.go](tests/TourOfGo/moretypes/typedef.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/moretypes/typedef.cpp)) | ✔️ |
| [TourOfGo/welcome/hello.go](tests/TourOfGo/welcome/hello.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/welcome/hello.cpp)) | ✔️ |
| [TourOfGo/welcome/sandbox.go](tests/TourOfGo/welcome/sandbox.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/welcome/sandbox.cpp)) | ❌ |
| [experiments/convs.go](tests/experiments/convs.go) | ✔️ | ❌ | ❌ | ❌ |


# Conversion of imported packages
| file | cpp generate | cpp compile |
| ---- | -------------| ----------- |
| $(ImportDir)/bufio/bufio.go | ✔️ ([cpp](generated/golang/bufio/bufio.cpp), [h](generated/golang/bufio/bufio.h))| ✔️ |
| $(ImportDir)/bytes/buffer.go | ✔️ ([cpp](generated/golang/bytes/buffer.cpp), [h](generated/golang/bytes/buffer.h))| ✔️ |
| $(ImportDir)/bytes/bytes.go | ✔️ ([cpp](generated/golang/bytes/bytes.cpp), [h](generated/golang/bytes/bytes.h))| ✔️ |
| $(ImportDir)/bytes/reader.go | ✔️ ([cpp](generated/golang/bytes/reader.cpp), [h](generated/golang/bytes/reader.h))| ✔️ |
| $(ImportDir)/cmp/cmp.go | ✔️ ([cpp](generated/golang/cmp/cmp.cpp), [h](generated/golang/cmp/cmp.h))| ✔️ |
| $(ImportDir)/compress/flate/deflate.go | ✔️ ([cpp](generated/golang/compress/flate/deflate.cpp), [h](generated/golang/compress/flate/deflate.h))| ✔️ |
| $(ImportDir)/compress/flate/deflatefast.go | ✔️ ([cpp](generated/golang/compress/flate/deflatefast.cpp), [h](generated/golang/compress/flate/deflatefast.h))| ❌ |
| $(ImportDir)/compress/flate/dict_decoder.go | ✔️ ([cpp](generated/golang/compress/flate/dict_decoder.cpp), [h](generated/golang/compress/flate/dict_decoder.h))| ✔️ |
| $(ImportDir)/compress/flate/huffman_bit_writer.go | ✔️ ([cpp](generated/golang/compress/flate/huffman_bit_writer.cpp), [h](generated/golang/compress/flate/huffman_bit_writer.h))| ❌ |
| $(ImportDir)/compress/flate/huffman_code.go | ✔️ ([cpp](generated/golang/compress/flate/huffman_code.cpp), [h](generated/golang/compress/flate/huffman_code.h))| ❌ |
| $(ImportDir)/compress/flate/inflate.go | ✔️ ([cpp](generated/golang/compress/flate/inflate.cpp), [h](generated/golang/compress/flate/inflate.h))| ✔️ |
| $(ImportDir)/compress/flate/level1.go | ✔️ ([cpp](generated/golang/compress/flate/level1.cpp), [h](generated/golang/compress/flate/level1.h))| ❌ |
| $(ImportDir)/compress/flate/level2.go | ✔️ ([cpp](generated/golang/compress/flate/level2.cpp), [h](generated/golang/compress/flate/level2.h))| ❌ |
| $(ImportDir)/compress/flate/level3.go | ✔️ ([cpp](generated/golang/compress/flate/level3.cpp), [h](generated/golang/compress/flate/level3.h))| ❌ |
| $(ImportDir)/compress/flate/level4.go | ✔️ ([cpp](generated/golang/compress/flate/level4.cpp), [h](generated/golang/compress/flate/level4.h))| ❌ |
| $(ImportDir)/compress/flate/level5.go | ✔️ ([cpp](generated/golang/compress/flate/level5.cpp), [h](generated/golang/compress/flate/level5.h))| ❌ |
| $(ImportDir)/compress/flate/level6.go | ✔️ ([cpp](generated/golang/compress/flate/level6.cpp), [h](generated/golang/compress/flate/level6.h))| ❌ |
| $(ImportDir)/compress/flate/load_store.go | ✔️ ([cpp](generated/golang/compress/flate/load_store.cpp), [h](generated/golang/compress/flate/load_store.h))| ✔️ |
| $(ImportDir)/compress/flate/regmask_amd64.go | ✔️ ([cpp](generated/golang/compress/flate/regmask_amd64.cpp), [h](generated/golang/compress/flate/regmask_amd64.h))| ✔️ |
| $(ImportDir)/compress/flate/token.go | ✔️ ([cpp](generated/golang/compress/flate/token.cpp), [h](generated/golang/compress/flate/token.h))| ✔️ |
| $(ImportDir)/compress/zlib/reader.go | ✔️ ([cpp](generated/golang/compress/zlib/reader.cpp), [h](generated/golang/compress/zlib/reader.h))| ✔️ |
| $(ImportDir)/compress/zlib/writer.go | ✔️ ([cpp](generated/golang/compress/zlib/writer.cpp), [h](generated/golang/compress/zlib/writer.h))| ✔️ |
| $(ImportDir)/container/heap/heap.go | ✔️ ([cpp](generated/golang/container/heap/heap.cpp), [h](generated/golang/container/heap/heap.h))| ✔️ |
| $(ImportDir)/context/context.go | ✔️ ([cpp](generated/golang/context/context.cpp), [h](generated/golang/context/context.h))| ❌ |
| $(ImportDir)/encoding/base32/base32.go | ✔️ ([cpp](generated/golang/encoding/base32/base32.cpp), [h](generated/golang/encoding/base32/base32.h))| ✔️ |
| $(ImportDir)/encoding/base64/base64.go | ✔️ ([cpp](generated/golang/encoding/base64/base64.cpp), [h](generated/golang/encoding/base64/base64.h))| ✔️ |
| $(ImportDir)/encoding/binary/binary.go | ✔️ ([cpp](generated/golang/encoding/binary/binary.cpp), [h](generated/golang/encoding/binary/binary.h))| ❌ |
| $(ImportDir)/encoding/binary/native_endian_little.go | ✔️ ([cpp](generated/golang/encoding/binary/native_endian_little.cpp), [h](generated/golang/encoding/binary/native_endian_little.h))| ✔️ |
| $(ImportDir)/encoding/binary/varint.go | ✔️ ([cpp](generated/golang/encoding/binary/varint.cpp), [h](generated/golang/encoding/binary/varint.h))| ✔️ |
| $(ImportDir)/encoding/encoding.go | ✔️ ([cpp](generated/golang/encoding/encoding.cpp), [h](generated/golang/encoding/encoding.h))| ✔️ |
| $(ImportDir)/encoding/hex/hex.go | ✔️ ([cpp](generated/golang/encoding/hex/hex.cpp), [h](generated/golang/encoding/hex/hex.h))| ✔️ |
| $(ImportDir)/encoding/json/internal/internal.go | ✔️ ([cpp](generated/golang/encoding/json/internal/internal.cpp), [h](generated/golang/encoding/json/internal/internal.h))| ✔️ |
| $(ImportDir)/encoding/json/internal/jsonflags/flags.go | ✔️ ([cpp](generated/golang/encoding/json/internal/jsonflags/flags.cpp), [h](generated/golang/encoding/json/internal/jsonflags/flags.h))| ❌ |
| $(ImportDir)/encoding/json/internal/jsonopts/options.go | ✔️ ([cpp](generated/golang/encoding/json/internal/jsonopts/options.cpp), [h](generated/golang/encoding/json/internal/jsonopts/options.h))| ❌ |
| $(ImportDir)/encoding/json/internal/jsonwire/decode.go | ✔️ ([cpp](generated/golang/encoding/json/internal/jsonwire/decode.cpp), [h](generated/golang/encoding/json/internal/jsonwire/decode.h))| ❌ |
| $(ImportDir)/encoding/json/internal/jsonwire/encode.go | ✔️ ([cpp](generated/golang/encoding/json/internal/jsonwire/encode.cpp), [h](generated/golang/encoding/json/internal/jsonwire/encode.h))| ❌ |
| $(ImportDir)/encoding/json/internal/jsonwire/wire.go | ✔️ ([cpp](generated/golang/encoding/json/internal/jsonwire/wire.cpp), [h](generated/golang/encoding/json/internal/jsonwire/wire.h))| ❌ |
| $(ImportDir)/encoding/json/jsontext/decode.go | ✔️ ([cpp](generated/golang/encoding/json/jsontext/decode.cpp), [h](generated/golang/encoding/json/jsontext/decode.h))| ❌ |
| $(ImportDir)/encoding/json/jsontext/doc.go | ✔️ ([cpp](generated/golang/encoding/json/jsontext/doc.cpp), [h](generated/golang/encoding/json/jsontext/doc.h))| ✔️ |
| $(ImportDir)/encoding/json/jsontext/encode.go | ✔️ ([cpp](generated/golang/encoding/json/jsontext/encode.cpp), [h](generated/golang/encoding/json/jsontext/encode.h))| ❌ |
| $(ImportDir)/encoding/json/jsontext/errors.go | ✔️ ([cpp](generated/golang/encoding/json/jsontext/errors.cpp), [h](generated/golang/encoding/json/jsontext/errors.h))| ❌ |
| $(ImportDir)/encoding/json/jsontext/export.go | ✔️ ([cpp](generated/golang/encoding/json/jsontext/export.cpp), [h](generated/golang/encoding/json/jsontext/export.h))| ❌ |
| $(ImportDir)/encoding/json/jsontext/options.go | ✔️ ([cpp](generated/golang/encoding/json/jsontext/options.cpp), [h](generated/golang/encoding/json/jsontext/options.h))| ❌ |
| $(ImportDir)/encoding/json/jsontext/pools.go | ✔️ ([cpp](generated/golang/encoding/json/jsontext/pools.cpp), [h](generated/golang/encoding/json/jsontext/pools.h))| ❌ |
| $(ImportDir)/encoding/json/jsontext/quote.go | ✔️ ([cpp](generated/golang/encoding/json/jsontext/quote.cpp), [h](generated/golang/encoding/json/jsontext/quote.h))| ❌ |
| $(ImportDir)/encoding/json/jsontext/state.go | ✔️ ([cpp](generated/golang/encoding/json/jsontext/state.cpp), [h](generated/golang/encoding/json/jsontext/state.h))| ❌ |
| $(ImportDir)/encoding/json/jsontext/token.go | ✔️ ([cpp](generated/golang/encoding/json/jsontext/token.cpp), [h](generated/golang/encoding/json/jsontext/token.h))| ❌ |
| $(ImportDir)/encoding/json/jsontext/value.go | ✔️ ([cpp](generated/golang/encoding/json/jsontext/value.cpp), [h](generated/golang/encoding/json/jsontext/value.h))| ❌ |
| $(ImportDir)/encoding/json/v2/arshal.go | ✔️ ([cpp](generated/golang/encoding/json/v2/arshal.cpp), [h](generated/golang/encoding/json/v2/arshal.h))| ❌ |
| $(ImportDir)/encoding/json/v2/arshal_any.go | ✔️ ([cpp](generated/golang/encoding/json/v2/arshal_any.cpp), [h](generated/golang/encoding/json/v2/arshal_any.h))| ❌ |
| $(ImportDir)/encoding/json/v2/arshal_default.go | ✔️ ([cpp](generated/golang/encoding/json/v2/arshal_default.cpp), [h](generated/golang/encoding/json/v2/arshal_default.h))| ❌ |
| $(ImportDir)/encoding/json/v2/arshal_embedded.go | ✔️ ([cpp](generated/golang/encoding/json/v2/arshal_embedded.cpp), [h](generated/golang/encoding/json/v2/arshal_embedded.h))| ❌ |
| $(ImportDir)/encoding/json/v2/arshal_funcs.go | ✔️ ([cpp](generated/golang/encoding/json/v2/arshal_funcs.cpp), [h](generated/golang/encoding/json/v2/arshal_funcs.h))| ❌ |
| $(ImportDir)/encoding/json/v2/arshal_methods.go | ✔️ ([cpp](generated/golang/encoding/json/v2/arshal_methods.cpp), [h](generated/golang/encoding/json/v2/arshal_methods.h))| ❌ |
| $(ImportDir)/encoding/json/v2/arshal_time.go | ✔️ ([cpp](generated/golang/encoding/json/v2/arshal_time.cpp), [h](generated/golang/encoding/json/v2/arshal_time.h))| ❌ |
| $(ImportDir)/encoding/json/v2/doc.go | ✔️ ([cpp](generated/golang/encoding/json/v2/doc.cpp), [h](generated/golang/encoding/json/v2/doc.h))| ✔️ |
| $(ImportDir)/encoding/json/v2/errors.go | ✔️ ([cpp](generated/golang/encoding/json/v2/errors.cpp), [h](generated/golang/encoding/json/v2/errors.h))| ❌ |
| $(ImportDir)/encoding/json/v2/fields.go | ✔️ ([cpp](generated/golang/encoding/json/v2/fields.cpp), [h](generated/golang/encoding/json/v2/fields.h))| ❌ |
| $(ImportDir)/encoding/json/v2/fold.go | ✔️ ([cpp](generated/golang/encoding/json/v2/fold.cpp), [h](generated/golang/encoding/json/v2/fold.h))| ✔️ |
| $(ImportDir)/encoding/json/v2/intern.go | ✔️ ([cpp](generated/golang/encoding/json/v2/intern.cpp), [h](generated/golang/encoding/json/v2/intern.h))| ❌ |
| $(ImportDir)/encoding/json/v2/options.go | ✔️ ([cpp](generated/golang/encoding/json/v2/options.cpp), [h](generated/golang/encoding/json/v2/options.h))| ❌ |
| $(ImportDir)/encoding/json/v2_decode.go | ✔️ ([cpp](generated/golang/encoding/json/v2_decode.cpp), [h](generated/golang/encoding/json/v2_decode.h))| ❌ |
| $(ImportDir)/encoding/json/v2_encode.go | ✔️ ([cpp](generated/golang/encoding/json/v2_encode.cpp), [h](generated/golang/encoding/json/v2_encode.h))| ❌ |
| $(ImportDir)/encoding/json/v2_indent.go | ✔️ ([cpp](generated/golang/encoding/json/v2_indent.cpp), [h](generated/golang/encoding/json/v2_indent.h))| ❌ |
| $(ImportDir)/encoding/json/v2_options.go | ✔️ ([cpp](generated/golang/encoding/json/v2_options.cpp), [h](generated/golang/encoding/json/v2_options.h))| ❌ |
| $(ImportDir)/encoding/json/v2_scanner.go | ✔️ ([cpp](generated/golang/encoding/json/v2_scanner.cpp), [h](generated/golang/encoding/json/v2_scanner.h))| ❌ |
| $(ImportDir)/encoding/json/v2_stream.go | ✔️ ([cpp](generated/golang/encoding/json/v2_stream.cpp), [h](generated/golang/encoding/json/v2_stream.h))| ❌ |
| $(ImportDir)/errors/errors.go | ✔️ ([cpp](generated/golang/errors/errors.cpp), [h](generated/golang/errors/errors.h))| ✔️ |
| $(ImportDir)/errors/wrap.go | ✔️ ([cpp](generated/golang/errors/wrap.cpp), [h](generated/golang/errors/wrap.h))| ✔️ |
| $(ImportDir)/fmt/errors.go | ✔️ ([cpp](generated/golang/fmt/errors.cpp), [h](generated/golang/fmt/errors.h))| ✔️ |
| $(ImportDir)/fmt/format.go | ✔️ ([cpp](generated/golang/fmt/format.cpp), [h](generated/golang/fmt/format.h))| ✔️ |
| $(ImportDir)/fmt/print.go | ✔️ ([cpp](generated/golang/fmt/print.cpp), [h](generated/golang/fmt/print.h))| ❌ |
| $(ImportDir)/fmt/scan.go | ✔️ ([cpp](generated/golang/fmt/scan.cpp), [h](generated/golang/fmt/scan.h))| ❌ |
| $(ImportDir)/go/ast/ast.go | ✔️ ([cpp](generated/golang/go/ast/ast.cpp), [h](generated/golang/go/ast/ast.h))| ❌ |
| $(ImportDir)/go/ast/directive.go | ✔️ ([cpp](generated/golang/go/ast/directive.cpp), [h](generated/golang/go/ast/directive.h))| ✔️ |
| $(ImportDir)/go/ast/scope.go | ✔️ ([cpp](generated/golang/go/ast/scope.cpp), [h](generated/golang/go/ast/scope.h))| ❌ |
| $(ImportDir)/go/ast/walk.go | ✔️ ([cpp](generated/golang/go/ast/walk.cpp), [h](generated/golang/go/ast/walk.h))| ✔️ |
| $(ImportDir)/go/build/build.go | ✔️ ([cpp](generated/golang/go/build/build.cpp), [h](generated/golang/go/build/build.h))| ❌ |
| $(ImportDir)/go/build/constraint/expr.go | ✔️ ([cpp](generated/golang/go/build/constraint/expr.cpp), [h](generated/golang/go/build/constraint/expr.h))| ❌ |
| $(ImportDir)/go/build/constraint/vers.go | ✔️ ([cpp](generated/golang/go/build/constraint/vers.cpp), [h](generated/golang/go/build/constraint/vers.h))| ❌ |
| $(ImportDir)/go/build/gc.go | ✔️ ([cpp](generated/golang/go/build/gc.cpp), [h](generated/golang/go/build/gc.h))| ❌ |
| $(ImportDir)/go/build/read.go | ✔️ ([cpp](generated/golang/go/build/read.cpp), [h](generated/golang/go/build/read.h))| ❌ |
| $(ImportDir)/go/constant/value.go | ✔️ ([cpp](generated/golang/go/constant/value.cpp), [h](generated/golang/go/constant/value.h))| ❌ |
| $(ImportDir)/go/doc/comment/html.go | ✔️ ([cpp](generated/golang/go/doc/comment/html.cpp), [h](generated/golang/go/doc/comment/html.h))| ❌ |
| $(ImportDir)/go/doc/comment/markdown.go | ✔️ ([cpp](generated/golang/go/doc/comment/markdown.cpp), [h](generated/golang/go/doc/comment/markdown.h))| ❌ |
| $(ImportDir)/go/doc/comment/parse.go | ✔️ ([cpp](generated/golang/go/doc/comment/parse.cpp), [h](generated/golang/go/doc/comment/parse.h))| ❌ |
| $(ImportDir)/go/doc/comment/print.go | ✔️ ([cpp](generated/golang/go/doc/comment/print.cpp), [h](generated/golang/go/doc/comment/print.h))| ❌ |
| $(ImportDir)/go/doc/comment/std.go | ✔️ ([cpp](generated/golang/go/doc/comment/std.cpp), [h](generated/golang/go/doc/comment/std.h))| ✔️ |
| $(ImportDir)/go/doc/comment/text.go | ✔️ ([cpp](generated/golang/go/doc/comment/text.cpp), [h](generated/golang/go/doc/comment/text.h))| ❌ |
| $(ImportDir)/go/doc/doc.go | ✔️ ([cpp](generated/golang/go/doc/doc.cpp), [h](generated/golang/go/doc/doc.h))| ❌ |
| $(ImportDir)/go/doc/example.go | ✔️ ([cpp](generated/golang/go/doc/example.cpp), [h](generated/golang/go/doc/example.h))| ❌ |
| $(ImportDir)/go/doc/exports.go | ✔️ ([cpp](generated/golang/go/doc/exports.cpp), [h](generated/golang/go/doc/exports.h))| ❌ |
| $(ImportDir)/go/doc/filter.go | ✔️ ([cpp](generated/golang/go/doc/filter.cpp), [h](generated/golang/go/doc/filter.h))| ✔️ |
| $(ImportDir)/go/doc/reader.go | ✔️ ([cpp](generated/golang/go/doc/reader.cpp), [h](generated/golang/go/doc/reader.h))| ❌ |
| $(ImportDir)/go/doc/synopsis.go | ✔️ ([cpp](generated/golang/go/doc/synopsis.cpp), [h](generated/golang/go/doc/synopsis.h))| ❌ |
| $(ImportDir)/go/parser/interface.go | ✔️ ([cpp](generated/golang/go/parser/interface.cpp), [h](generated/golang/go/parser/interface.h))| ❌ |
| $(ImportDir)/go/parser/parser.go | ✔️ ([cpp](generated/golang/go/parser/parser.cpp), [h](generated/golang/go/parser/parser.h))| ❌ |
| $(ImportDir)/go/parser/resolver.go | ✔️ ([cpp](generated/golang/go/parser/resolver.cpp), [h](generated/golang/go/parser/resolver.h))| ❌ |
| $(ImportDir)/go/scanner/errors.go | ✔️ ([cpp](generated/golang/go/scanner/errors.cpp), [h](generated/golang/go/scanner/errors.h))| ❌ |
| $(ImportDir)/go/scanner/scanner.go | ✔️ ([cpp](generated/golang/go/scanner/scanner.cpp), [h](generated/golang/go/scanner/scanner.h))| ❌ |
| $(ImportDir)/go/token/position.go | ✔️ ([cpp](generated/golang/go/token/position.cpp), [h](generated/golang/go/token/position.h))| ❌ |
| $(ImportDir)/go/token/token.go | ✔️ ([cpp](generated/golang/go/token/token.cpp), [h](generated/golang/go/token/token.h))| ❌ |
| $(ImportDir)/go/token/tree.go | ✔️ ([cpp](generated/golang/go/token/tree.cpp), [h](generated/golang/go/token/tree.h))| ❌ |
| $(ImportDir)/go/types/alias.go | ✔️ ([cpp](generated/golang/go/types/alias.cpp), [h](generated/golang/go/types/alias.h))| ❌ |
| $(ImportDir)/go/types/api.go | ✔️ ([cpp](generated/golang/go/types/api.cpp), [h](generated/golang/go/types/api.h))| ❌ |
| $(ImportDir)/go/types/api_predicates.go | ✔️ ([cpp](generated/golang/go/types/api_predicates.cpp), [h](generated/golang/go/types/api_predicates.h))| ❌ |
| $(ImportDir)/go/types/array.go | ✔️ ([cpp](generated/golang/go/types/array.cpp), [h](generated/golang/go/types/array.h))| ❌ |
| $(ImportDir)/go/types/assignments.go | ✔️ ([cpp](generated/golang/go/types/assignments.cpp), [h](generated/golang/go/types/assignments.h))| ❌ |
| $(ImportDir)/go/types/basic.go | ✔️ ([cpp](generated/golang/go/types/basic.cpp), [h](generated/golang/go/types/basic.h))| ❌ |
| $(ImportDir)/go/types/builtins.go | ✔️ ([cpp](generated/golang/go/types/builtins.cpp), [h](generated/golang/go/types/builtins.h))| ❌ |
| $(ImportDir)/go/types/call.go | ✔️ ([cpp](generated/golang/go/types/call.cpp), [h](generated/golang/go/types/call.h))| ❌ |
| $(ImportDir)/go/types/chan.go | ✔️ ([cpp](generated/golang/go/types/chan.cpp), [h](generated/golang/go/types/chan.h))| ❌ |
| $(ImportDir)/go/types/check.go | ✔️ ([cpp](generated/golang/go/types/check.cpp), [h](generated/golang/go/types/check.h))| ❌ |
| $(ImportDir)/go/types/const.go | ✔️ ([cpp](generated/golang/go/types/const.cpp), [h](generated/golang/go/types/const.h))| ❌ |
| $(ImportDir)/go/types/context.go | ✔️ ([cpp](generated/golang/go/types/context.cpp), [h](generated/golang/go/types/context.h))| ❌ |
| $(ImportDir)/go/types/conversions.go | ✔️ ([cpp](generated/golang/go/types/conversions.cpp), [h](generated/golang/go/types/conversions.h))| ❌ |
| $(ImportDir)/go/types/cycles.go | ✔️ ([cpp](generated/golang/go/types/cycles.cpp), [h](generated/golang/go/types/cycles.h))| ❌ |
| $(ImportDir)/go/types/decl.go | ✔️ ([cpp](generated/golang/go/types/decl.cpp), [h](generated/golang/go/types/decl.h))| ❌ |
| $(ImportDir)/go/types/errors.go | ✔️ ([cpp](generated/golang/go/types/errors.cpp), [h](generated/golang/go/types/errors.h))| ❌ |
| $(ImportDir)/go/types/errsupport.go | ✔️ ([cpp](generated/golang/go/types/errsupport.cpp), [h](generated/golang/go/types/errsupport.h))| ❌ |
| $(ImportDir)/go/types/expr.go | ✔️ ([cpp](generated/golang/go/types/expr.cpp), [h](generated/golang/go/types/expr.h))| ❌ |
| $(ImportDir)/go/types/exprstring.go | ✔️ ([cpp](generated/golang/go/types/exprstring.cpp), [h](generated/golang/go/types/exprstring.h))| ❌ |
| $(ImportDir)/go/types/format.go | ✔️ ([cpp](generated/golang/go/types/format.cpp), [h](generated/golang/go/types/format.h))| ❌ |
| $(ImportDir)/go/types/gccgosizes.go | ✔️ ([cpp](generated/golang/go/types/gccgosizes.cpp), [h](generated/golang/go/types/gccgosizes.h))| ❌ |
| $(ImportDir)/go/types/gcsizes.go | ✔️ ([cpp](generated/golang/go/types/gcsizes.cpp), [h](generated/golang/go/types/gcsizes.h))| ❌ |
| $(ImportDir)/go/types/index.go | ✔️ ([cpp](generated/golang/go/types/index.cpp), [h](generated/golang/go/types/index.h))| ❌ |
| $(ImportDir)/go/types/infer.go | ✔️ ([cpp](generated/golang/go/types/infer.cpp), [h](generated/golang/go/types/infer.h))| ❌ |
| $(ImportDir)/go/types/initorder.go | ✔️ ([cpp](generated/golang/go/types/initorder.cpp), [h](generated/golang/go/types/initorder.h))| ❌ |
| $(ImportDir)/go/types/instantiate.go | ✔️ ([cpp](generated/golang/go/types/instantiate.cpp), [h](generated/golang/go/types/instantiate.h))| ❌ |
| $(ImportDir)/go/types/interface.go | ✔️ ([cpp](generated/golang/go/types/interface.cpp), [h](generated/golang/go/types/interface.h))| ❌ |
| $(ImportDir)/go/types/iter.go | ✔️ ([cpp](generated/golang/go/types/iter.cpp), [h](generated/golang/go/types/iter.h))| ❌ |
| $(ImportDir)/go/types/labels.go | ✔️ ([cpp](generated/golang/go/types/labels.cpp), [h](generated/golang/go/types/labels.h))| ❌ |
| $(ImportDir)/go/types/literals.go | ✔️ ([cpp](generated/golang/go/types/literals.cpp), [h](generated/golang/go/types/literals.h))| ❌ |
| $(ImportDir)/go/types/lookup.go | ✔️ ([cpp](generated/golang/go/types/lookup.cpp), [h](generated/golang/go/types/lookup.h))| ❌ |
| $(ImportDir)/go/types/map.go | ✔️ ([cpp](generated/golang/go/types/map.cpp), [h](generated/golang/go/types/map.h))| ❌ |
| $(ImportDir)/go/types/methodset.go | ✔️ ([cpp](generated/golang/go/types/methodset.cpp), [h](generated/golang/go/types/methodset.h))| ❌ |
| $(ImportDir)/go/types/mono.go | ✔️ ([cpp](generated/golang/go/types/mono.cpp), [h](generated/golang/go/types/mono.h))| ❌ |
| $(ImportDir)/go/types/named.go | ✔️ ([cpp](generated/golang/go/types/named.cpp), [h](generated/golang/go/types/named.h))| ❌ |
| $(ImportDir)/go/types/object.go | ✔️ ([cpp](generated/golang/go/types/object.cpp), [h](generated/golang/go/types/object.h))| ❌ |
| $(ImportDir)/go/types/objset.go | ✔️ ([cpp](generated/golang/go/types/objset.cpp), [h](generated/golang/go/types/objset.h))| ❌ |
| $(ImportDir)/go/types/operand.go | ✔️ ([cpp](generated/golang/go/types/operand.cpp), [h](generated/golang/go/types/operand.h))| ❌ |
| $(ImportDir)/go/types/package.go | ✔️ ([cpp](generated/golang/go/types/package.cpp), [h](generated/golang/go/types/package.h))| ❌ |
| $(ImportDir)/go/types/pointer.go | ✔️ ([cpp](generated/golang/go/types/pointer.cpp), [h](generated/golang/go/types/pointer.h))| ❌ |
| $(ImportDir)/go/types/predicates.go | ✔️ ([cpp](generated/golang/go/types/predicates.cpp), [h](generated/golang/go/types/predicates.h))| ❌ |
| $(ImportDir)/go/types/range.go | ✔️ ([cpp](generated/golang/go/types/range.cpp), [h](generated/golang/go/types/range.h))| ❌ |
| $(ImportDir)/go/types/recording.go | ✔️ ([cpp](generated/golang/go/types/recording.cpp), [h](generated/golang/go/types/recording.h))| ❌ |
| $(ImportDir)/go/types/resolver.go | ✔️ ([cpp](generated/golang/go/types/resolver.cpp), [h](generated/golang/go/types/resolver.h))| ❌ |
| $(ImportDir)/go/types/return.go | ✔️ ([cpp](generated/golang/go/types/return.cpp), [h](generated/golang/go/types/return.h))| ❌ |
| $(ImportDir)/go/types/scope.go | ✔️ ([cpp](generated/golang/go/types/scope.cpp), [h](generated/golang/go/types/scope.h))| ❌ |
| $(ImportDir)/go/types/selection.go | ✔️ ([cpp](generated/golang/go/types/selection.cpp), [h](generated/golang/go/types/selection.h))| ❌ |
| $(ImportDir)/go/types/signature.go | ✔️ ([cpp](generated/golang/go/types/signature.cpp), [h](generated/golang/go/types/signature.h))| ❌ |
| $(ImportDir)/go/types/sizes.go | ✔️ ([cpp](generated/golang/go/types/sizes.cpp), [h](generated/golang/go/types/sizes.h))| ❌ |
| $(ImportDir)/go/types/slice.go | ✔️ ([cpp](generated/golang/go/types/slice.cpp), [h](generated/golang/go/types/slice.h))| ❌ |
| $(ImportDir)/go/types/stmt.go | ✔️ ([cpp](generated/golang/go/types/stmt.cpp), [h](generated/golang/go/types/stmt.h))| ❌ |
| $(ImportDir)/go/types/struct.go | ✔️ ([cpp](generated/golang/go/types/struct.cpp), [h](generated/golang/go/types/struct.h))| ❌ |
| $(ImportDir)/go/types/subst.go | ✔️ ([cpp](generated/golang/go/types/subst.cpp), [h](generated/golang/go/types/subst.h))| ❌ |
| $(ImportDir)/go/types/termlist.go | ✔️ ([cpp](generated/golang/go/types/termlist.cpp), [h](generated/golang/go/types/termlist.h))| ❌ |
| $(ImportDir)/go/types/trie.go | ✔️ ([cpp](generated/golang/go/types/trie.cpp), [h](generated/golang/go/types/trie.h))| ❌ |
| $(ImportDir)/go/types/tuple.go | ✔️ ([cpp](generated/golang/go/types/tuple.cpp), [h](generated/golang/go/types/tuple.h))| ❌ |
| $(ImportDir)/go/types/type.go | ✔️ ([cpp](generated/golang/go/types/type.cpp), [h](generated/golang/go/types/type.h))| ✔️ |
| $(ImportDir)/go/types/typelists.go | ✔️ ([cpp](generated/golang/go/types/typelists.cpp), [h](generated/golang/go/types/typelists.h))| ❌ |
| $(ImportDir)/go/types/typeparam.go | ✔️ ([cpp](generated/golang/go/types/typeparam.cpp), [h](generated/golang/go/types/typeparam.h))| ❌ |
| $(ImportDir)/go/types/typeset.go | ✔️ ([cpp](generated/golang/go/types/typeset.cpp), [h](generated/golang/go/types/typeset.h))| ❌ |
| $(ImportDir)/go/types/typestring.go | ✔️ ([cpp](generated/golang/go/types/typestring.cpp), [h](generated/golang/go/types/typestring.h))| ❌ |
| $(ImportDir)/go/types/typeterm.go | ✔️ ([cpp](generated/golang/go/types/typeterm.cpp), [h](generated/golang/go/types/typeterm.h))| ❌ |
| $(ImportDir)/go/types/typexpr.go | ✔️ ([cpp](generated/golang/go/types/typexpr.cpp), [h](generated/golang/go/types/typexpr.h))| ❌ |
| $(ImportDir)/go/types/under.go | ✔️ ([cpp](generated/golang/go/types/under.cpp), [h](generated/golang/go/types/under.h))| ❌ |
| $(ImportDir)/go/types/unify.go | ✔️ ([cpp](generated/golang/go/types/unify.cpp), [h](generated/golang/go/types/unify.h))| ❌ |
| $(ImportDir)/go/types/union.go | ✔️ ([cpp](generated/golang/go/types/union.cpp), [h](generated/golang/go/types/union.h))| ❌ |
| $(ImportDir)/go/types/universe.go | ✔️ ([cpp](generated/golang/go/types/universe.cpp), [h](generated/golang/go/types/universe.h))| ❌ |
| $(ImportDir)/go/types/util.go | ✔️ ([cpp](generated/golang/go/types/util.cpp), [h](generated/golang/go/types/util.h))| ❌ |
| $(ImportDir)/go/types/validtype.go | ✔️ ([cpp](generated/golang/go/types/validtype.cpp), [h](generated/golang/go/types/validtype.h))| ❌ |
| $(ImportDir)/go/types/version.go | ✔️ ([cpp](generated/golang/go/types/version.cpp), [h](generated/golang/go/types/version.h))| ❌ |
| $(ImportDir)/go/version/version.go | ✔️ ([cpp](generated/golang/go/version/version.cpp), [h](generated/golang/go/version/version.h))| ✔️ |
| $(ImportDir)/golang.org/x/mod/semver/semver.go | ✔️ ([cpp](generated/golang/golang.org/x/mod/semver/semver.cpp), [h](generated/golang/golang.org/x/mod/semver/semver.h))| ❌ |
| $(ImportDir)/golang.org/x/sync/errgroup/errgroup.go | ✔️ ([cpp](generated/golang/golang.org/x/sync/errgroup/errgroup.cpp), [h](generated/golang/golang.org/x/sync/errgroup/errgroup.h))| ❌ |
| $(ImportDir)/golang.org/x/tools/go/ast/edge/edge.go | ✔️ ([cpp](generated/golang/golang.org/x/tools/go/ast/edge/edge.cpp), [h](generated/golang/golang.org/x/tools/go/ast/edge/edge.h))| ❌ |
| $(ImportDir)/golang.org/x/tools/go/ast/inspector/cursor.go | ✔️ ([cpp](generated/golang/golang.org/x/tools/go/ast/inspector/cursor.cpp), [h](generated/golang/golang.org/x/tools/go/ast/inspector/cursor.h))| ❌ |
| $(ImportDir)/golang.org/x/tools/go/ast/inspector/inspector.go | ✔️ ([cpp](generated/golang/golang.org/x/tools/go/ast/inspector/inspector.cpp), [h](generated/golang/golang.org/x/tools/go/ast/inspector/inspector.h))| ❌ |
| $(ImportDir)/golang.org/x/tools/go/ast/inspector/typeof.go | ✔️ ([cpp](generated/golang/golang.org/x/tools/go/ast/inspector/typeof.cpp), [h](generated/golang/golang.org/x/tools/go/ast/inspector/typeof.h))| ✔️ |
| $(ImportDir)/golang.org/x/tools/go/ast/inspector/walk.go | ✔️ ([cpp](generated/golang/golang.org/x/tools/go/ast/inspector/walk.cpp), [h](generated/golang/golang.org/x/tools/go/ast/inspector/walk.h))| ✔️ |
| $(ImportDir)/golang.org/x/tools/go/gcexportdata/gcexportdata.go | ✔️ ([cpp](generated/golang/golang.org/x/tools/go/gcexportdata/gcexportdata.cpp), [h](generated/golang/golang.org/x/tools/go/gcexportdata/gcexportdata.h))| ❌ |
| $(ImportDir)/golang.org/x/tools/go/packages/external.go | ✔️ ([cpp](generated/golang/golang.org/x/tools/go/packages/external.cpp), [h](generated/golang/golang.org/x/tools/go/packages/external.h))| ❌ |
| $(ImportDir)/golang.org/x/tools/go/packages/golist.go | ✔️ ([cpp](generated/golang/golang.org/x/tools/go/packages/golist.cpp), [h](generated/golang/golang.org/x/tools/go/packages/golist.h))| ❌ |
| $(ImportDir)/golang.org/x/tools/go/packages/golist_overlay.go | ✔️ ([cpp](generated/golang/golang.org/x/tools/go/packages/golist_overlay.cpp), [h](generated/golang/golang.org/x/tools/go/packages/golist_overlay.h))| ❌ |
| $(ImportDir)/golang.org/x/tools/go/packages/packages.go | ✔️ ([cpp](generated/golang/golang.org/x/tools/go/packages/packages.cpp), [h](generated/golang/golang.org/x/tools/go/packages/packages.h))| ❌ |
| $(ImportDir)/golang.org/x/tools/go/types/objectpath/objectpath.go | ✔️ ([cpp](generated/golang/golang.org/x/tools/go/types/objectpath/objectpath.cpp), [h](generated/golang/golang.org/x/tools/go/types/objectpath/objectpath.h))| ❌ |
| $(ImportDir)/golang.org/x/tools/internal/aliases/aliases.go | ✔️ ([cpp](generated/golang/golang.org/x/tools/internal/aliases/aliases.cpp), [h](generated/golang/golang.org/x/tools/internal/aliases/aliases.h))| ❌ |
| $(ImportDir)/golang.org/x/tools/internal/event/core/event.go | ✔️ ([cpp](generated/golang/golang.org/x/tools/internal/event/core/event.cpp), [h](generated/golang/golang.org/x/tools/internal/event/core/event.h))| ❌ |
| $(ImportDir)/golang.org/x/tools/internal/event/core/export.go | ✔️ ([cpp](generated/golang/golang.org/x/tools/internal/event/core/export.cpp), [h](generated/golang/golang.org/x/tools/internal/event/core/export.h))| ✔️ |
| $(ImportDir)/golang.org/x/tools/internal/event/event.go | ✔️ ([cpp](generated/golang/golang.org/x/tools/internal/event/event.cpp), [h](generated/golang/golang.org/x/tools/internal/event/event.h))| ✔️ |
| $(ImportDir)/golang.org/x/tools/internal/event/keys/keys.go | ✔️ ([cpp](generated/golang/golang.org/x/tools/internal/event/keys/keys.cpp), [h](generated/golang/golang.org/x/tools/internal/event/keys/keys.h))| ❌ |
| $(ImportDir)/golang.org/x/tools/internal/event/keys/standard.go | ✔️ ([cpp](generated/golang/golang.org/x/tools/internal/event/keys/standard.cpp), [h](generated/golang/golang.org/x/tools/internal/event/keys/standard.h))| ❌ |
| $(ImportDir)/golang.org/x/tools/internal/event/label/label.go | ✔️ ([cpp](generated/golang/golang.org/x/tools/internal/event/label/label.cpp), [h](generated/golang/golang.org/x/tools/internal/event/label/label.h))| ❌ |
| $(ImportDir)/golang.org/x/tools/internal/gcimporter/bimport.go | ✔️ ([cpp](generated/golang/golang.org/x/tools/internal/gcimporter/bimport.cpp), [h](generated/golang/golang.org/x/tools/internal/gcimporter/bimport.h))| ✔️ |
| $(ImportDir)/golang.org/x/tools/internal/gcimporter/exportdata.go | ✔️ ([cpp](generated/golang/golang.org/x/tools/internal/gcimporter/exportdata.cpp), [h](generated/golang/golang.org/x/tools/internal/gcimporter/exportdata.h))| ❌ |
| $(ImportDir)/golang.org/x/tools/internal/gcimporter/gcimporter.go | ✔️ ([cpp](generated/golang/golang.org/x/tools/internal/gcimporter/gcimporter.cpp), [h](generated/golang/golang.org/x/tools/internal/gcimporter/gcimporter.h))| ❌ |
| $(ImportDir)/golang.org/x/tools/internal/gcimporter/iexport.go | ✔️ ([cpp](generated/golang/golang.org/x/tools/internal/gcimporter/iexport.cpp), [h](generated/golang/golang.org/x/tools/internal/gcimporter/iexport.h))| ❌ |
| $(ImportDir)/golang.org/x/tools/internal/gcimporter/iimport.go | ✔️ ([cpp](generated/golang/golang.org/x/tools/internal/gcimporter/iimport.cpp), [h](generated/golang/golang.org/x/tools/internal/gcimporter/iimport.h))| ❌ |
| $(ImportDir)/golang.org/x/tools/internal/gcimporter/predeclared.go | ✔️ ([cpp](generated/golang/golang.org/x/tools/internal/gcimporter/predeclared.cpp), [h](generated/golang/golang.org/x/tools/internal/gcimporter/predeclared.h))| ❌ |
| $(ImportDir)/golang.org/x/tools/internal/gcimporter/support.go | ✔️ ([cpp](generated/golang/golang.org/x/tools/internal/gcimporter/support.cpp), [h](generated/golang/golang.org/x/tools/internal/gcimporter/support.h))| ❌ |
| $(ImportDir)/golang.org/x/tools/internal/gcimporter/ureader.go | ✔️ ([cpp](generated/golang/golang.org/x/tools/internal/gcimporter/ureader.cpp), [h](generated/golang/golang.org/x/tools/internal/gcimporter/ureader.h))| ❌ |
| $(ImportDir)/golang.org/x/tools/internal/gocommand/invoke.go | ✔️ ([cpp](generated/golang/golang.org/x/tools/internal/gocommand/invoke.cpp), [h](generated/golang/golang.org/x/tools/internal/gocommand/invoke.h))| ❌ |
| $(ImportDir)/golang.org/x/tools/internal/gocommand/invoke_notunix.go | ✔️ ([cpp](generated/golang/golang.org/x/tools/internal/gocommand/invoke_notunix.cpp), [h](generated/golang/golang.org/x/tools/internal/gocommand/invoke_notunix.h))| ❌ |
| $(ImportDir)/golang.org/x/tools/internal/gocommand/vendor.go | ✔️ ([cpp](generated/golang/golang.org/x/tools/internal/gocommand/vendor.cpp), [h](generated/golang/golang.org/x/tools/internal/gocommand/vendor.h))| ❌ |
| $(ImportDir)/golang.org/x/tools/internal/gocommand/version.go | ✔️ ([cpp](generated/golang/golang.org/x/tools/internal/gocommand/version.cpp), [h](generated/golang/golang.org/x/tools/internal/gocommand/version.h))| ❌ |
| $(ImportDir)/golang.org/x/tools/internal/packagesinternal/packages.go | ✔️ ([cpp](generated/golang/golang.org/x/tools/internal/packagesinternal/packages.cpp), [h](generated/golang/golang.org/x/tools/internal/packagesinternal/packages.h))| ✔️ |
| $(ImportDir)/golang.org/x/tools/internal/pkgbits/codes.go | ✔️ ([cpp](generated/golang/golang.org/x/tools/internal/pkgbits/codes.cpp), [h](generated/golang/golang.org/x/tools/internal/pkgbits/codes.h))| ❌ |
| $(ImportDir)/golang.org/x/tools/internal/pkgbits/decoder.go | ✔️ ([cpp](generated/golang/golang.org/x/tools/internal/pkgbits/decoder.cpp), [h](generated/golang/golang.org/x/tools/internal/pkgbits/decoder.h))| ❌ |
| $(ImportDir)/golang.org/x/tools/internal/pkgbits/flags.go | ✔️ ([cpp](generated/golang/golang.org/x/tools/internal/pkgbits/flags.cpp), [h](generated/golang/golang.org/x/tools/internal/pkgbits/flags.h))| ✔️ |
| $(ImportDir)/golang.org/x/tools/internal/pkgbits/reloc.go | ✔️ ([cpp](generated/golang/golang.org/x/tools/internal/pkgbits/reloc.cpp), [h](generated/golang/golang.org/x/tools/internal/pkgbits/reloc.h))| ✔️ |
| $(ImportDir)/golang.org/x/tools/internal/pkgbits/support.go | ✔️ ([cpp](generated/golang/golang.org/x/tools/internal/pkgbits/support.cpp), [h](generated/golang/golang.org/x/tools/internal/pkgbits/support.h))| ❌ |
| $(ImportDir)/golang.org/x/tools/internal/pkgbits/sync.go | ✔️ ([cpp](generated/golang/golang.org/x/tools/internal/pkgbits/sync.cpp), [h](generated/golang/golang.org/x/tools/internal/pkgbits/sync.h))| ❌ |
| $(ImportDir)/golang.org/x/tools/internal/pkgbits/version.go | ✔️ ([cpp](generated/golang/golang.org/x/tools/internal/pkgbits/version.cpp), [h](generated/golang/golang.org/x/tools/internal/pkgbits/version.h))| ✔️ |
| $(ImportDir)/golang.org/x/tools/internal/typesinternal/errorcode.go | ✔️ ([cpp](generated/golang/golang.org/x/tools/internal/typesinternal/errorcode.cpp), [h](generated/golang/golang.org/x/tools/internal/typesinternal/errorcode.h))| ❌ |
| $(ImportDir)/golang.org/x/tools/internal/typesinternal/recv.go | ✔️ ([cpp](generated/golang/golang.org/x/tools/internal/typesinternal/recv.cpp), [h](generated/golang/golang.org/x/tools/internal/typesinternal/recv.h))| ❌ |
| $(ImportDir)/golang.org/x/tools/internal/typesinternal/types.go | ✔️ ([cpp](generated/golang/golang.org/x/tools/internal/typesinternal/types.cpp), [h](generated/golang/golang.org/x/tools/internal/typesinternal/types.h))| ❌ |
| $(ImportDir)/golang.org/x/tools/internal/typesinternal/varkind.go | ✔️ ([cpp](generated/golang/golang.org/x/tools/internal/typesinternal/varkind.cpp), [h](generated/golang/golang.org/x/tools/internal/typesinternal/varkind.h))| ❌ |
| $(ImportDir)/golang.org/x/tour/pic/pic.go | ✔️ ([cpp](generated/golang/golang.org/x/tour/pic/pic.cpp), [h](generated/golang/golang.org/x/tour/pic/pic.h))| ❌ |
| $(ImportDir)/golang.org/x/tour/reader/validate.go | ✔️ ([cpp](generated/golang/golang.org/x/tour/reader/validate.cpp), [h](generated/golang/golang.org/x/tour/reader/validate.h))| ❌ |
| $(ImportDir)/golang.org/x/tour/tree/tree.go | ✔️ ([cpp](generated/golang/golang.org/x/tour/tree/tree.cpp), [h](generated/golang/golang.org/x/tour/tree/tree.h))| ❌ |
| $(ImportDir)/golang.org/x/tour/wc/wc.go | ✔️ ([cpp](generated/golang/golang.org/x/tour/wc/wc.cpp), [h](generated/golang/golang.org/x/tour/wc/wc.h))| ❌ |
| $(ImportDir)/hash/adler32/adler32.go | ✔️ ([cpp](generated/golang/hash/adler32/adler32.cpp), [h](generated/golang/hash/adler32/adler32.h))| ✔️ |
| $(ImportDir)/hash/crc32/crc32.go | ✔️ ([cpp](generated/golang/hash/crc32/crc32.cpp), [h](generated/golang/hash/crc32/crc32.h))| ✔️ |
| $(ImportDir)/hash/crc32/crc32_amd64.go | ✔️ ([cpp](generated/golang/hash/crc32/crc32_amd64.cpp), [h](generated/golang/hash/crc32/crc32_amd64.h))| ✔️ |
| $(ImportDir)/hash/crc32/crc32_generic.go | ✔️ ([cpp](generated/golang/hash/crc32/crc32_generic.cpp), [h](generated/golang/hash/crc32/crc32_generic.h))| ✔️ |
| $(ImportDir)/hash/hash.go | ✔️ ([cpp](generated/golang/hash/hash.cpp), [h](generated/golang/hash/hash.h))| ✔️ |
| $(ImportDir)/image/color/color.go | ✔️ ([cpp](generated/golang/image/color/color.cpp), [h](generated/golang/image/color/color.h))| ✔️ |
| $(ImportDir)/image/color/ycbcr.go | ✔️ ([cpp](generated/golang/image/color/ycbcr.cpp), [h](generated/golang/image/color/ycbcr.h))| ✔️ |
| $(ImportDir)/image/format.go | ✔️ ([cpp](generated/golang/image/format.cpp), [h](generated/golang/image/format.h))| ✔️ |
| $(ImportDir)/image/geom.go | ✔️ ([cpp](generated/golang/image/geom.cpp), [h](generated/golang/image/geom.h))| ✔️ |
| $(ImportDir)/image/image.go | ✔️ ([cpp](generated/golang/image/image.cpp), [h](generated/golang/image/image.h))| ❌ |
| $(ImportDir)/image/png/paeth.go | ✔️ ([cpp](generated/golang/image/png/paeth.cpp), [h](generated/golang/image/png/paeth.h))| ✔️ |
| $(ImportDir)/image/png/reader.go | ✔️ ([cpp](generated/golang/image/png/reader.cpp), [h](generated/golang/image/png/reader.h))| ❌ |
| $(ImportDir)/image/png/writer.go | ✔️ ([cpp](generated/golang/image/png/writer.cpp), [h](generated/golang/image/png/writer.h))| ❌ |
| $(ImportDir)/internal/abi/abi.go | ✔️ ([cpp](generated/golang/internal/abi/abi.cpp), [h](generated/golang/internal/abi/abi.h))| ❌ |
| $(ImportDir)/internal/abi/abi_amd64.go | ✔️ ([cpp](generated/golang/internal/abi/abi_amd64.cpp), [h](generated/golang/internal/abi/abi_amd64.h))| ✔️ |
| $(ImportDir)/internal/abi/bounds.go | ✔️ ([cpp](generated/golang/internal/abi/bounds.cpp), [h](generated/golang/internal/abi/bounds.h))| ✔️ |
| $(ImportDir)/internal/abi/escape.go | ✔️ ([cpp](generated/golang/internal/abi/escape.cpp), [h](generated/golang/internal/abi/escape.h))| ✔️ |
| $(ImportDir)/internal/abi/funcpc.go | ✔️ ([cpp](generated/golang/internal/abi/funcpc.cpp), [h](generated/golang/internal/abi/funcpc.h))| ✔️ |
| $(ImportDir)/internal/abi/iface.go | ✔️ ([cpp](generated/golang/internal/abi/iface.cpp), [h](generated/golang/internal/abi/iface.h))| ✔️ |
| $(ImportDir)/internal/abi/map.go | ✔️ ([cpp](generated/golang/internal/abi/map.cpp), [h](generated/golang/internal/abi/map.h))| ✔️ |
| $(ImportDir)/internal/abi/rangefuncconsts.go | ✔️ ([cpp](generated/golang/internal/abi/rangefuncconsts.cpp), [h](generated/golang/internal/abi/rangefuncconsts.h))| ✔️ |
| $(ImportDir)/internal/abi/runtime.go | ✔️ ([cpp](generated/golang/internal/abi/runtime.cpp), [h](generated/golang/internal/abi/runtime.h))| ✔️ |
| $(ImportDir)/internal/abi/stack.go | ✔️ ([cpp](generated/golang/internal/abi/stack.cpp), [h](generated/golang/internal/abi/stack.h))| ✔️ |
| $(ImportDir)/internal/abi/switch.go | ✔️ ([cpp](generated/golang/internal/abi/switch.cpp), [h](generated/golang/internal/abi/switch.h))| ✔️ |
| $(ImportDir)/internal/abi/symtab.go | ✔️ ([cpp](generated/golang/internal/abi/symtab.cpp), [h](generated/golang/internal/abi/symtab.h))| ✔️ |
| $(ImportDir)/internal/abi/type.go | ✔️ ([cpp](generated/golang/internal/abi/type.cpp), [h](generated/golang/internal/abi/type.h))| ❌ |
| $(ImportDir)/internal/asan/noasan.go | ✔️ ([cpp](generated/golang/internal/asan/noasan.cpp), [h](generated/golang/internal/asan/noasan.h))| ✔️ |
| $(ImportDir)/internal/bisect/bisect.go | ✔️ ([cpp](generated/golang/internal/bisect/bisect.cpp), [h](generated/golang/internal/bisect/bisect.h))| ❌ |
| $(ImportDir)/internal/buildcfg/cfg.go | ✔️ ([cpp](generated/golang/internal/buildcfg/cfg.cpp), [h](generated/golang/internal/buildcfg/cfg.h))| ❌ |
| $(ImportDir)/internal/buildcfg/exp.go | ✔️ ([cpp](generated/golang/internal/buildcfg/exp.cpp), [h](generated/golang/internal/buildcfg/exp.h))| ❌ |
| $(ImportDir)/internal/buildcfg/zbootstrap.go | ✔️ ([cpp](generated/golang/internal/buildcfg/zbootstrap.cpp), [h](generated/golang/internal/buildcfg/zbootstrap.h))| ❌ |
| $(ImportDir)/internal/bytealg/bytealg.go | ✔️ ([cpp](generated/golang/internal/bytealg/bytealg.cpp), [h](generated/golang/internal/bytealg/bytealg.h))| ✔️ |
| $(ImportDir)/internal/bytealg/compare_native.go | ✔️ ([cpp](generated/golang/internal/bytealg/compare_native.cpp), [h](generated/golang/internal/bytealg/compare_native.h))| ✔️ |
| $(ImportDir)/internal/bytealg/count_native.go | ✔️ ([cpp](generated/golang/internal/bytealg/count_native.cpp), [h](generated/golang/internal/bytealg/count_native.h))| ✔️ |
| $(ImportDir)/internal/bytealg/equal_generic.go | ✔️ ([cpp](generated/golang/internal/bytealg/equal_generic.cpp), [h](generated/golang/internal/bytealg/equal_generic.h))| ✔️ |
| $(ImportDir)/internal/bytealg/index_amd64.go | ✔️ ([cpp](generated/golang/internal/bytealg/index_amd64.cpp), [h](generated/golang/internal/bytealg/index_amd64.h))| ✔️ |
| $(ImportDir)/internal/bytealg/index_native.go | ✔️ ([cpp](generated/golang/internal/bytealg/index_native.cpp), [h](generated/golang/internal/bytealg/index_native.h))| ✔️ |
| $(ImportDir)/internal/bytealg/indexbyte_native.go | ✔️ ([cpp](generated/golang/internal/bytealg/indexbyte_native.cpp), [h](generated/golang/internal/bytealg/indexbyte_native.h))| ✔️ |
| $(ImportDir)/internal/bytealg/lastindexbyte_generic.go | ✔️ ([cpp](generated/golang/internal/bytealg/lastindexbyte_generic.cpp), [h](generated/golang/internal/bytealg/lastindexbyte_generic.h))| ✔️ |
| $(ImportDir)/internal/byteorder/byteorder.go | ✔️ ([cpp](generated/golang/internal/byteorder/byteorder.cpp), [h](generated/golang/internal/byteorder/byteorder.h))| ✔️ |
| $(ImportDir)/internal/chacha8rand/chacha8.go | ✔️ ([cpp](generated/golang/internal/chacha8rand/chacha8.cpp), [h](generated/golang/internal/chacha8rand/chacha8.h))| ✔️ |
| $(ImportDir)/internal/cpu/cpu.go | ✔️ ([cpp](generated/golang/internal/cpu/cpu.cpp), [h](generated/golang/internal/cpu/cpu.h))| ❌ |
| $(ImportDir)/internal/cpu/cpu_x86.go | ✔️ ([cpp](generated/golang/internal/cpu/cpu_x86.cpp), [h](generated/golang/internal/cpu/cpu_x86.h))| ❌ |
| $(ImportDir)/internal/cpu/cpu_x86_other.go | ✔️ ([cpp](generated/golang/internal/cpu/cpu_x86_other.cpp), [h](generated/golang/internal/cpu/cpu_x86_other.h))| ✔️ |
| $(ImportDir)/internal/filepathlite/path.go | ✔️ ([cpp](generated/golang/internal/filepathlite/path.cpp), [h](generated/golang/internal/filepathlite/path.h))| ✔️ |
| $(ImportDir)/internal/filepathlite/path_windows.go | ✔️ ([cpp](generated/golang/internal/filepathlite/path_windows.cpp), [h](generated/golang/internal/filepathlite/path_windows.h))| ✔️ |
| $(ImportDir)/internal/fmtsort/sort.go | ✔️ ([cpp](generated/golang/internal/fmtsort/sort.cpp), [h](generated/golang/internal/fmtsort/sort.h))| ❌ |
| $(ImportDir)/internal/goarch/goarch.go | ✔️ ([cpp](generated/golang/internal/goarch/goarch.cpp), [h](generated/golang/internal/goarch/goarch.h))| ✔️ |
| $(ImportDir)/internal/goarch/goarch_amd64.go | ✔️ ([cpp](generated/golang/internal/goarch/goarch_amd64.cpp), [h](generated/golang/internal/goarch/goarch_amd64.h))| ❌ |
| $(ImportDir)/internal/goarch/zgoarch_amd64.go | ✔️ ([cpp](generated/golang/internal/goarch/zgoarch_amd64.cpp), [h](generated/golang/internal/goarch/zgoarch_amd64.h))| ✔️ |
| $(ImportDir)/internal/godebug/godebug.go | ✔️ ([cpp](generated/golang/internal/godebug/godebug.cpp), [h](generated/golang/internal/godebug/godebug.h))| ❌ |
| $(ImportDir)/internal/godebugs/table.go | ✔️ ([cpp](generated/golang/internal/godebugs/table.cpp), [h](generated/golang/internal/godebugs/table.h))| ❌ |
| $(ImportDir)/internal/goexperiment/exp_cgocheck2_off.go | ✔️ ([cpp](generated/golang/internal/goexperiment/exp_cgocheck2_off.cpp), [h](generated/golang/internal/goexperiment/exp_cgocheck2_off.h))| ✔️ |
| $(ImportDir)/internal/goexperiment/exp_greenteagc_on.go | ✔️ ([cpp](generated/golang/internal/goexperiment/exp_greenteagc_on.cpp), [h](generated/golang/internal/goexperiment/exp_greenteagc_on.h))| ✔️ |
| $(ImportDir)/internal/goexperiment/exp_heapminimum512kib_off.go | ✔️ ([cpp](generated/golang/internal/goexperiment/exp_heapminimum512kib_off.cpp), [h](generated/golang/internal/goexperiment/exp_heapminimum512kib_off.h))| ✔️ |
| $(ImportDir)/internal/goexperiment/exp_mapsplitgroup_off.go | ✔️ ([cpp](generated/golang/internal/goexperiment/exp_mapsplitgroup_off.cpp), [h](generated/golang/internal/goexperiment/exp_mapsplitgroup_off.h))| ✔️ |
| $(ImportDir)/internal/goexperiment/exp_randomizedheapbase64_on.go | ✔️ ([cpp](generated/golang/internal/goexperiment/exp_randomizedheapbase64_on.cpp), [h](generated/golang/internal/goexperiment/exp_randomizedheapbase64_on.h))| ✔️ |
| $(ImportDir)/internal/goexperiment/exp_runtimefreegc_off.go | ✔️ ([cpp](generated/golang/internal/goexperiment/exp_runtimefreegc_off.cpp), [h](generated/golang/internal/goexperiment/exp_runtimefreegc_off.h))| ✔️ |
| $(ImportDir)/internal/goexperiment/exp_runtimesecret_off.go | ✔️ ([cpp](generated/golang/internal/goexperiment/exp_runtimesecret_off.cpp), [h](generated/golang/internal/goexperiment/exp_runtimesecret_off.h))| ✔️ |
| $(ImportDir)/internal/goexperiment/exp_sizespecializedmalloc_on.go | ✔️ ([cpp](generated/golang/internal/goexperiment/exp_sizespecializedmalloc_on.cpp), [h](generated/golang/internal/goexperiment/exp_sizespecializedmalloc_on.h))| ✔️ |
| $(ImportDir)/internal/goexperiment/flags.go | ✔️ ([cpp](generated/golang/internal/goexperiment/flags.cpp), [h](generated/golang/internal/goexperiment/flags.h))| ✔️ |
| $(ImportDir)/internal/goos/zgoos_windows.go | ✔️ ([cpp](generated/golang/internal/goos/zgoos_windows.cpp), [h](generated/golang/internal/goos/zgoos_windows.h))| ✔️ |
| $(ImportDir)/internal/goroot/gc.go | ✔️ ([cpp](generated/golang/internal/goroot/gc.cpp), [h](generated/golang/internal/goroot/gc.h))| ❌ |
| $(ImportDir)/internal/gover/gover.go | ✔️ ([cpp](generated/golang/internal/gover/gover.cpp), [h](generated/golang/internal/gover/gover.h))| ✔️ |
| $(ImportDir)/internal/goversion/goversion.go | ✔️ ([cpp](generated/golang/internal/goversion/goversion.cpp), [h](generated/golang/internal/goversion/goversion.h))| ✔️ |
| $(ImportDir)/internal/lazyregexp/lazyre.go | ✔️ ([cpp](generated/golang/internal/lazyregexp/lazyre.cpp), [h](generated/golang/internal/lazyregexp/lazyre.h))| ❌ |
| $(ImportDir)/internal/msan/nomsan.go | ✔️ ([cpp](generated/golang/internal/msan/nomsan.cpp), [h](generated/golang/internal/msan/nomsan.h))| ✔️ |
| $(ImportDir)/internal/oserror/errors.go | ✔️ ([cpp](generated/golang/internal/oserror/errors.cpp), [h](generated/golang/internal/oserror/errors.h))| ✔️ |
| $(ImportDir)/internal/platform/supported.go | ✔️ ([cpp](generated/golang/internal/platform/supported.cpp), [h](generated/golang/internal/platform/supported.h))| ❌ |
| $(ImportDir)/internal/platform/zosarch.go | ✔️ ([cpp](generated/golang/internal/platform/zosarch.cpp), [h](generated/golang/internal/platform/zosarch.h))| ❌ |
| $(ImportDir)/internal/poll/errno_windows.go | ✔️ ([cpp](generated/golang/internal/poll/errno_windows.cpp), [h](generated/golang/internal/poll/errno_windows.h))| ❌ |
| $(ImportDir)/internal/poll/fd.go | ✔️ ([cpp](generated/golang/internal/poll/fd.cpp), [h](generated/golang/internal/poll/fd.h))| ✔️ |
| $(ImportDir)/internal/poll/fd_fsync_windows.go | ✔️ ([cpp](generated/golang/internal/poll/fd_fsync_windows.cpp), [h](generated/golang/internal/poll/fd_fsync_windows.h))| ❌ |
| $(ImportDir)/internal/poll/fd_mutex.go | ✔️ ([cpp](generated/golang/internal/poll/fd_mutex.cpp), [h](generated/golang/internal/poll/fd_mutex.h))| ❌ |
| $(ImportDir)/internal/poll/fd_poll_runtime.go | ✔️ ([cpp](generated/golang/internal/poll/fd_poll_runtime.cpp), [h](generated/golang/internal/poll/fd_poll_runtime.h))| ❌ |
| $(ImportDir)/internal/poll/fd_posix.go | ✔️ ([cpp](generated/golang/internal/poll/fd_posix.cpp), [h](generated/golang/internal/poll/fd_posix.h))| ❌ |
| $(ImportDir)/internal/poll/fd_windows.go | ✔️ ([cpp](generated/golang/internal/poll/fd_windows.cpp), [h](generated/golang/internal/poll/fd_windows.h))| ❌ |
| $(ImportDir)/internal/poll/hook_windows.go | ✔️ ([cpp](generated/golang/internal/poll/hook_windows.cpp), [h](generated/golang/internal/poll/hook_windows.h))| ❌ |
| $(ImportDir)/internal/profilerecord/profilerecord.go | ✔️ ([cpp](generated/golang/internal/profilerecord/profilerecord.cpp), [h](generated/golang/internal/profilerecord/profilerecord.h))| ✔️ |
| $(ImportDir)/internal/race/norace.go | ✔️ ([cpp](generated/golang/internal/race/norace.cpp), [h](generated/golang/internal/race/norace.h))| ✔️ |
| $(ImportDir)/internal/reflectlite/swapper.go | ✔️ ([cpp](generated/golang/internal/reflectlite/swapper.cpp), [h](generated/golang/internal/reflectlite/swapper.h))| ✔️ |
| $(ImportDir)/internal/reflectlite/type.go | ✔️ ([cpp](generated/golang/internal/reflectlite/type.cpp), [h](generated/golang/internal/reflectlite/type.h))| ❌ |
| $(ImportDir)/internal/reflectlite/value.go | ✔️ ([cpp](generated/golang/internal/reflectlite/value.cpp), [h](generated/golang/internal/reflectlite/value.h))| ❌ |
| $(ImportDir)/internal/runtime/atomic/atomic_amd64.go | ✔️ ([cpp](generated/golang/internal/runtime/atomic/atomic_amd64.cpp), [h](generated/golang/internal/runtime/atomic/atomic_amd64.h))| ✔️ |
| $(ImportDir)/internal/runtime/atomic/stubs.go | ✔️ ([cpp](generated/golang/internal/runtime/atomic/stubs.cpp), [h](generated/golang/internal/runtime/atomic/stubs.h))| ✔️ |
| $(ImportDir)/internal/runtime/atomic/types.go | ✔️ ([cpp](generated/golang/internal/runtime/atomic/types.cpp), [h](generated/golang/internal/runtime/atomic/types.h))| ✔️ |
| $(ImportDir)/internal/runtime/exithook/hooks.go | ✔️ ([cpp](generated/golang/internal/runtime/exithook/hooks.cpp), [h](generated/golang/internal/runtime/exithook/hooks.h))| ✔️ |
| $(ImportDir)/internal/runtime/gc/malloc.go | ✔️ ([cpp](generated/golang/internal/runtime/gc/malloc.cpp), [h](generated/golang/internal/runtime/gc/malloc.h))| ✔️ |
| $(ImportDir)/internal/runtime/gc/scan.go | ✔️ ([cpp](generated/golang/internal/runtime/gc/scan.cpp), [h](generated/golang/internal/runtime/gc/scan.h))| ✔️ |
| $(ImportDir)/internal/runtime/gc/scan/filter_amd64.go | ✔️ ([cpp](generated/golang/internal/runtime/gc/scan/filter_amd64.cpp), [h](generated/golang/internal/runtime/gc/scan/filter_amd64.h))| ✔️ |
| $(ImportDir)/internal/runtime/gc/scan/scan_amd64.go | ✔️ ([cpp](generated/golang/internal/runtime/gc/scan/scan_amd64.cpp), [h](generated/golang/internal/runtime/gc/scan/scan_amd64.h))| ✔️ |
| $(ImportDir)/internal/runtime/gc/sizeclasses.go | ✔️ ([cpp](generated/golang/internal/runtime/gc/sizeclasses.cpp), [h](generated/golang/internal/runtime/gc/sizeclasses.h))| ✔️ |
| $(ImportDir)/internal/runtime/maps/group.go | ✔️ ([cpp](generated/golang/internal/runtime/maps/group.cpp), [h](generated/golang/internal/runtime/maps/group.h))| ❌ |
| $(ImportDir)/internal/runtime/maps/map.go | ✔️ ([cpp](generated/golang/internal/runtime/maps/map.cpp), [h](generated/golang/internal/runtime/maps/map.h))| ❌ |
| $(ImportDir)/internal/runtime/maps/memhash_aes.go | ✔️ ([cpp](generated/golang/internal/runtime/maps/memhash_aes.cpp), [h](generated/golang/internal/runtime/maps/memhash_aes.h))| ❌ |
| $(ImportDir)/internal/runtime/maps/memhash_aes_asm.go | ✔️ ([cpp](generated/golang/internal/runtime/maps/memhash_aes_asm.cpp), [h](generated/golang/internal/runtime/maps/memhash_aes_asm.h))| ✔️ |
| $(ImportDir)/internal/runtime/maps/memhash_align_check.go | ✔️ ([cpp](generated/golang/internal/runtime/maps/memhash_align_check.cpp), [h](generated/golang/internal/runtime/maps/memhash_align_check.h))| ✔️ |
| $(ImportDir)/internal/runtime/maps/runtime.go | ✔️ ([cpp](generated/golang/internal/runtime/maps/runtime.cpp), [h](generated/golang/internal/runtime/maps/runtime.h))| ✔️ |
| $(ImportDir)/internal/runtime/maps/runtime_alg.go | ✔️ ([cpp](generated/golang/internal/runtime/maps/runtime_alg.cpp), [h](generated/golang/internal/runtime/maps/runtime_alg.h))| ❌ |
| $(ImportDir)/internal/runtime/maps/runtime_hash64.go | ✔️ ([cpp](generated/golang/internal/runtime/maps/runtime_hash64.cpp), [h](generated/golang/internal/runtime/maps/runtime_hash64.h))| ✔️ |
| $(ImportDir)/internal/runtime/maps/table.go | ✔️ ([cpp](generated/golang/internal/runtime/maps/table.cpp), [h](generated/golang/internal/runtime/maps/table.h))| ❌ |
| $(ImportDir)/internal/runtime/maps/table_debug.go | ✔️ ([cpp](generated/golang/internal/runtime/maps/table_debug.cpp), [h](generated/golang/internal/runtime/maps/table_debug.h))| ❌ |
| $(ImportDir)/internal/runtime/math/math.go | ✔️ ([cpp](generated/golang/internal/runtime/math/math.cpp), [h](generated/golang/internal/runtime/math/math.h))| ❌ |
| $(ImportDir)/internal/runtime/pprof/label/labelset.go | ✔️ ([cpp](generated/golang/internal/runtime/pprof/label/labelset.cpp), [h](generated/golang/internal/runtime/pprof/label/labelset.h))| ✔️ |
| $(ImportDir)/internal/runtime/sys/consts.go | ✔️ ([cpp](generated/golang/internal/runtime/sys/consts.cpp), [h](generated/golang/internal/runtime/sys/consts.h))| ✔️ |
| $(ImportDir)/internal/runtime/sys/consts_norace.go | ✔️ ([cpp](generated/golang/internal/runtime/sys/consts_norace.cpp), [h](generated/golang/internal/runtime/sys/consts_norace.h))| ✔️ |
| $(ImportDir)/internal/runtime/sys/intrinsics.go | ✔️ ([cpp](generated/golang/internal/runtime/sys/intrinsics.cpp), [h](generated/golang/internal/runtime/sys/intrinsics.h))| ✔️ |
| $(ImportDir)/internal/runtime/sys/nih.go | ✔️ ([cpp](generated/golang/internal/runtime/sys/nih.cpp), [h](generated/golang/internal/runtime/sys/nih.h))| ✔️ |
| $(ImportDir)/internal/runtime/sys/no_dit.go | ✔️ ([cpp](generated/golang/internal/runtime/sys/no_dit.cpp), [h](generated/golang/internal/runtime/sys/no_dit.h))| ✔️ |
| $(ImportDir)/internal/runtime/syscall/windows/defs_windows.go | ✔️ ([cpp](generated/golang/internal/runtime/syscall/windows/defs_windows.cpp), [h](generated/golang/internal/runtime/syscall/windows/defs_windows.h))| ✔️ |
| $(ImportDir)/internal/runtime/syscall/windows/defs_windows_amd64.go | ✔️ ([cpp](generated/golang/internal/runtime/syscall/windows/defs_windows_amd64.cpp), [h](generated/golang/internal/runtime/syscall/windows/defs_windows_amd64.h))| ✔️ |
| $(ImportDir)/internal/runtime/syscall/windows/syscall_windows.go | ✔️ ([cpp](generated/golang/internal/runtime/syscall/windows/syscall_windows.cpp), [h](generated/golang/internal/runtime/syscall/windows/syscall_windows.h))| ✔️ |
| $(ImportDir)/internal/strconv/atob.go | ✔️ ([cpp](generated/golang/internal/strconv/atob.cpp), [h](generated/golang/internal/strconv/atob.h))| ✔️ |
| $(ImportDir)/internal/strconv/atoc.go | ✔️ ([cpp](generated/golang/internal/strconv/atoc.cpp), [h](generated/golang/internal/strconv/atoc.h))| ❌ |
| $(ImportDir)/internal/strconv/atof.go | ✔️ ([cpp](generated/golang/internal/strconv/atof.cpp), [h](generated/golang/internal/strconv/atof.h))| ✔️ |
| $(ImportDir)/internal/strconv/atoi.go | ✔️ ([cpp](generated/golang/internal/strconv/atoi.cpp), [h](generated/golang/internal/strconv/atoi.h))| ❌ |
| $(ImportDir)/internal/strconv/ctoa.go | ✔️ ([cpp](generated/golang/internal/strconv/ctoa.cpp), [h](generated/golang/internal/strconv/ctoa.h))| ✔️ |
| $(ImportDir)/internal/strconv/decimal.go | ✔️ ([cpp](generated/golang/internal/strconv/decimal.cpp), [h](generated/golang/internal/strconv/decimal.h))| ✔️ |
| $(ImportDir)/internal/strconv/deps.go | ✔️ ([cpp](generated/golang/internal/strconv/deps.cpp), [h](generated/golang/internal/strconv/deps.h))| ✔️ |
| $(ImportDir)/internal/strconv/ftoa.go | ✔️ ([cpp](generated/golang/internal/strconv/ftoa.cpp), [h](generated/golang/internal/strconv/ftoa.h))| ❌ |
| $(ImportDir)/internal/strconv/itoa.go | ✔️ ([cpp](generated/golang/internal/strconv/itoa.cpp), [h](generated/golang/internal/strconv/itoa.h))| ❌ |
| $(ImportDir)/internal/strconv/pow10tab.go | ✔️ ([cpp](generated/golang/internal/strconv/pow10tab.cpp), [h](generated/golang/internal/strconv/pow10tab.h))| ✔️ |
| $(ImportDir)/internal/strconv/uscale.go | ✔️ ([cpp](generated/golang/internal/strconv/uscale.cpp), [h](generated/golang/internal/strconv/uscale.h))| ❌ |
| $(ImportDir)/internal/stringslite/strings.go | ✔️ ([cpp](generated/golang/internal/stringslite/strings.cpp), [h](generated/golang/internal/stringslite/strings.h))| ❌ |
| $(ImportDir)/internal/sync/hashtriemap.go | ✔️ ([cpp](generated/golang/internal/sync/hashtriemap.cpp), [h](generated/golang/internal/sync/hashtriemap.h))| ❌ |
| $(ImportDir)/internal/sync/mutex.go | ✔️ ([cpp](generated/golang/internal/sync/mutex.cpp), [h](generated/golang/internal/sync/mutex.h))| ❌ |
| $(ImportDir)/internal/sync/runtime.go | ✔️ ([cpp](generated/golang/internal/sync/runtime.cpp), [h](generated/golang/internal/sync/runtime.h))| ✔️ |
| $(ImportDir)/internal/synctest/synctest.go | ✔️ ([cpp](generated/golang/internal/synctest/synctest.cpp), [h](generated/golang/internal/synctest/synctest.h))| ✔️ |
| $(ImportDir)/internal/syscall/execenv/execenv_windows.go | ✔️ ([cpp](generated/golang/internal/syscall/execenv/execenv_windows.cpp), [h](generated/golang/internal/syscall/execenv/execenv_windows.h))| ❌ |
| $(ImportDir)/internal/syscall/windows/at_windows.go | ✔️ ([cpp](generated/golang/internal/syscall/windows/at_windows.cpp), [h](generated/golang/internal/syscall/windows/at_windows.h))| ❌ |
| $(ImportDir)/internal/syscall/windows/net_windows.go | ✔️ ([cpp](generated/golang/internal/syscall/windows/net_windows.cpp), [h](generated/golang/internal/syscall/windows/net_windows.h))| ❌ |
| $(ImportDir)/internal/syscall/windows/nonblocking_windows.go | ✔️ ([cpp](generated/golang/internal/syscall/windows/nonblocking_windows.cpp), [h](generated/golang/internal/syscall/windows/nonblocking_windows.h))| ❌ |
| $(ImportDir)/internal/syscall/windows/psapi_windows.go | ✔️ ([cpp](generated/golang/internal/syscall/windows/psapi_windows.cpp), [h](generated/golang/internal/syscall/windows/psapi_windows.h))| ✔️ |
| $(ImportDir)/internal/syscall/windows/registry/key.go | ✔️ ([cpp](generated/golang/internal/syscall/windows/registry/key.cpp), [h](generated/golang/internal/syscall/windows/registry/key.h))| ❌ |
| $(ImportDir)/internal/syscall/windows/registry/syscall.go | ✔️ ([cpp](generated/golang/internal/syscall/windows/registry/syscall.cpp), [h](generated/golang/internal/syscall/windows/registry/syscall.h))| ❌ |
| $(ImportDir)/internal/syscall/windows/registry/value.go | ✔️ ([cpp](generated/golang/internal/syscall/windows/registry/value.cpp), [h](generated/golang/internal/syscall/windows/registry/value.h))| ❌ |
| $(ImportDir)/internal/syscall/windows/registry/zsyscall_windows.go | ✔️ ([cpp](generated/golang/internal/syscall/windows/registry/zsyscall_windows.cpp), [h](generated/golang/internal/syscall/windows/registry/zsyscall_windows.h))| ✔️ |
| $(ImportDir)/internal/syscall/windows/reparse_windows.go | ✔️ ([cpp](generated/golang/internal/syscall/windows/reparse_windows.cpp), [h](generated/golang/internal/syscall/windows/reparse_windows.h))| ❌ |
| $(ImportDir)/internal/syscall/windows/security_windows.go | ✔️ ([cpp](generated/golang/internal/syscall/windows/security_windows.cpp), [h](generated/golang/internal/syscall/windows/security_windows.h))| ❌ |
| $(ImportDir)/internal/syscall/windows/string_windows.go | ✔️ ([cpp](generated/golang/internal/syscall/windows/string_windows.cpp), [h](generated/golang/internal/syscall/windows/string_windows.h))| ❌ |
| $(ImportDir)/internal/syscall/windows/symlink_windows.go | ✔️ ([cpp](generated/golang/internal/syscall/windows/symlink_windows.cpp), [h](generated/golang/internal/syscall/windows/symlink_windows.h))| ❌ |
| $(ImportDir)/internal/syscall/windows/syscall_windows.go | ✔️ ([cpp](generated/golang/internal/syscall/windows/syscall_windows.cpp), [h](generated/golang/internal/syscall/windows/syscall_windows.h))| ❌ |
| $(ImportDir)/internal/syscall/windows/sysdll/sysdll.go | ✔️ ([cpp](generated/golang/internal/syscall/windows/sysdll/sysdll.cpp), [h](generated/golang/internal/syscall/windows/sysdll/sysdll.h))| ✔️ |
| $(ImportDir)/internal/syscall/windows/types_windows.go | ✔️ ([cpp](generated/golang/internal/syscall/windows/types_windows.cpp), [h](generated/golang/internal/syscall/windows/types_windows.h))| ❌ |
| $(ImportDir)/internal/syscall/windows/version_windows.go | ✔️ ([cpp](generated/golang/internal/syscall/windows/version_windows.cpp), [h](generated/golang/internal/syscall/windows/version_windows.h))| ❌ |
| $(ImportDir)/internal/syscall/windows/zsyscall_windows.go | ✔️ ([cpp](generated/golang/internal/syscall/windows/zsyscall_windows.cpp), [h](generated/golang/internal/syscall/windows/zsyscall_windows.h))| ✔️ |
| $(ImportDir)/internal/syslist/syslist.go | ✔️ ([cpp](generated/golang/internal/syslist/syslist.cpp), [h](generated/golang/internal/syslist/syslist.h))| ✔️ |
| $(ImportDir)/internal/testlog/exit.go | ✔️ ([cpp](generated/golang/internal/testlog/exit.cpp), [h](generated/golang/internal/testlog/exit.h))| ✔️ |
| $(ImportDir)/internal/testlog/log.go | ✔️ ([cpp](generated/golang/internal/testlog/log.cpp), [h](generated/golang/internal/testlog/log.h))| ✔️ |
| $(ImportDir)/internal/trace/tracev2/events.go | ✔️ ([cpp](generated/golang/internal/trace/tracev2/events.cpp), [h](generated/golang/internal/trace/tracev2/events.h))| ❌ |
| $(ImportDir)/internal/trace/tracev2/spec.go | ✔️ ([cpp](generated/golang/internal/trace/tracev2/spec.cpp), [h](generated/golang/internal/trace/tracev2/spec.h))| ✔️ |
| $(ImportDir)/internal/types/errors/codes.go | ✔️ ([cpp](generated/golang/internal/types/errors/codes.cpp), [h](generated/golang/internal/types/errors/codes.h))| ❌ |
| $(ImportDir)/internal/unsafeheader/unsafeheader.go | ✔️ ([cpp](generated/golang/internal/unsafeheader/unsafeheader.cpp), [h](generated/golang/internal/unsafeheader/unsafeheader.h))| ✔️ |
| $(ImportDir)/io/fs/format.go | ✔️ ([cpp](generated/golang/io/fs/format.cpp), [h](generated/golang/io/fs/format.h))| ❌ |
| $(ImportDir)/io/fs/fs.go | ✔️ ([cpp](generated/golang/io/fs/fs.cpp), [h](generated/golang/io/fs/fs.h))| ✔️ |
| $(ImportDir)/io/fs/readdir.go | ✔️ ([cpp](generated/golang/io/fs/readdir.cpp), [h](generated/golang/io/fs/readdir.h))| ❌ |
| $(ImportDir)/io/fs/readfile.go | ✔️ ([cpp](generated/golang/io/fs/readfile.cpp), [h](generated/golang/io/fs/readfile.h))| ✔️ |
| $(ImportDir)/io/fs/readlink.go | ✔️ ([cpp](generated/golang/io/fs/readlink.cpp), [h](generated/golang/io/fs/readlink.h))| ✔️ |
| $(ImportDir)/io/fs/stat.go | ✔️ ([cpp](generated/golang/io/fs/stat.cpp), [h](generated/golang/io/fs/stat.h))| ✔️ |
| $(ImportDir)/io/fs/walk.go | ✔️ ([cpp](generated/golang/io/fs/walk.cpp), [h](generated/golang/io/fs/walk.h))| ✔️ |
| $(ImportDir)/io/io.go | ✔️ ([cpp](generated/golang/io/io.cpp), [h](generated/golang/io/io.h))| ✔️ |
| $(ImportDir)/iter/iter.go | ✔️ ([cpp](generated/golang/iter/iter.cpp), [h](generated/golang/iter/iter.h))| ❌ |
| $(ImportDir)/log/internal/internal.go | ✔️ ([cpp](generated/golang/log/internal/internal.cpp), [h](generated/golang/log/internal/internal.h))| ✔️ |
| $(ImportDir)/log/log.go | ✔️ ([cpp](generated/golang/log/log.cpp), [h](generated/golang/log/log.h))| ❌ |
| $(ImportDir)/math/abs.go | ✔️ ([cpp](generated/golang/math/abs.cpp), [h](generated/golang/math/abs.h))| ❌ |
| $(ImportDir)/math/big/arith.go | ✔️ ([cpp](generated/golang/math/big/arith.cpp), [h](generated/golang/math/big/arith.h))| ❌ |
| $(ImportDir)/math/big/arith_decl.go | ✔️ ([cpp](generated/golang/math/big/arith_decl.cpp), [h](generated/golang/math/big/arith_decl.h))| ❌ |
| $(ImportDir)/math/big/decimal.go | ✔️ ([cpp](generated/golang/math/big/decimal.cpp), [h](generated/golang/math/big/decimal.h))| ❌ |
| $(ImportDir)/math/big/float.go | ✔️ ([cpp](generated/golang/math/big/float.cpp), [h](generated/golang/math/big/float.h))| ❌ |
| $(ImportDir)/math/big/floatconv.go | ✔️ ([cpp](generated/golang/math/big/floatconv.cpp), [h](generated/golang/math/big/floatconv.h))| ❌ |
| $(ImportDir)/math/big/floatmarsh.go | ✔️ ([cpp](generated/golang/math/big/floatmarsh.cpp), [h](generated/golang/math/big/floatmarsh.h))| ❌ |
| $(ImportDir)/math/big/ftoa.go | ✔️ ([cpp](generated/golang/math/big/ftoa.cpp), [h](generated/golang/math/big/ftoa.h))| ❌ |
| $(ImportDir)/math/big/int.go | ✔️ ([cpp](generated/golang/math/big/int.cpp), [h](generated/golang/math/big/int.h))| ❌ |
| $(ImportDir)/math/big/intconv.go | ✔️ ([cpp](generated/golang/math/big/intconv.cpp), [h](generated/golang/math/big/intconv.h))| ❌ |
| $(ImportDir)/math/big/nat.go | ✔️ ([cpp](generated/golang/math/big/nat.cpp), [h](generated/golang/math/big/nat.h))| ❌ |
| $(ImportDir)/math/big/natconv.go | ✔️ ([cpp](generated/golang/math/big/natconv.cpp), [h](generated/golang/math/big/natconv.h))| ❌ |
| $(ImportDir)/math/big/natdiv.go | ✔️ ([cpp](generated/golang/math/big/natdiv.cpp), [h](generated/golang/math/big/natdiv.h))| ❌ |
| $(ImportDir)/math/big/natmul.go | ✔️ ([cpp](generated/golang/math/big/natmul.cpp), [h](generated/golang/math/big/natmul.h))| ❌ |
| $(ImportDir)/math/big/rat.go | ✔️ ([cpp](generated/golang/math/big/rat.cpp), [h](generated/golang/math/big/rat.h))| ❌ |
| $(ImportDir)/math/big/ratconv.go | ✔️ ([cpp](generated/golang/math/big/ratconv.cpp), [h](generated/golang/math/big/ratconv.h))| ❌ |
| $(ImportDir)/math/bits.go | ✔️ ([cpp](generated/golang/math/bits.cpp), [h](generated/golang/math/bits.h))| ✔️ |
| $(ImportDir)/math/bits/bits.go | ✔️ ([cpp](generated/golang/math/bits/bits.cpp), [h](generated/golang/math/bits/bits.h))| ❌ |
| $(ImportDir)/math/bits/bits_errors.go | ✔️ ([cpp](generated/golang/math/bits/bits_errors.cpp), [h](generated/golang/math/bits/bits_errors.h))| ✔️ |
| $(ImportDir)/math/bits/bits_tables.go | ✔️ ([cpp](generated/golang/math/bits/bits_tables.cpp), [h](generated/golang/math/bits/bits_tables.h))| ✔️ |
| $(ImportDir)/math/cmplx/sqrt.go | ✔️ ([cpp](generated/golang/math/cmplx/sqrt.cpp), [h](generated/golang/math/cmplx/sqrt.h))| ✔️ |
| $(ImportDir)/math/const.go | ✔️ ([cpp](generated/golang/math/const.cpp), [h](generated/golang/math/const.h))| ✔️ |
| $(ImportDir)/math/copysign.go | ✔️ ([cpp](generated/golang/math/copysign.cpp), [h](generated/golang/math/copysign.h))| ❌ |
| $(ImportDir)/math/exp.go | ✔️ ([cpp](generated/golang/math/exp.cpp), [h](generated/golang/math/exp.h))| ✔️ |
| $(ImportDir)/math/exp2_noasm.go | ✔️ ([cpp](generated/golang/math/exp2_noasm.cpp), [h](generated/golang/math/exp2_noasm.h))| ✔️ |
| $(ImportDir)/math/exp_asm.go | ✔️ ([cpp](generated/golang/math/exp_asm.cpp), [h](generated/golang/math/exp_asm.h))| ✔️ |
| $(ImportDir)/math/floor.go | ✔️ ([cpp](generated/golang/math/floor.cpp), [h](generated/golang/math/floor.h))| ❌ |
| $(ImportDir)/math/floor_asm.go | ✔️ ([cpp](generated/golang/math/floor_asm.cpp), [h](generated/golang/math/floor_asm.h))| ✔️ |
| $(ImportDir)/math/frexp.go | ✔️ ([cpp](generated/golang/math/frexp.cpp), [h](generated/golang/math/frexp.h))| ❌ |
| $(ImportDir)/math/hypot.go | ✔️ ([cpp](generated/golang/math/hypot.cpp), [h](generated/golang/math/hypot.h))| ✔️ |
| $(ImportDir)/math/hypot_asm.go | ✔️ ([cpp](generated/golang/math/hypot_asm.cpp), [h](generated/golang/math/hypot_asm.h))| ✔️ |
| $(ImportDir)/math/ldexp.go | ✔️ ([cpp](generated/golang/math/ldexp.cpp), [h](generated/golang/math/ldexp.h))| ❌ |
| $(ImportDir)/math/log.go | ✔️ ([cpp](generated/golang/math/log.cpp), [h](generated/golang/math/log.h))| ✔️ |
| $(ImportDir)/math/log10.go | ✔️ ([cpp](generated/golang/math/log10.cpp), [h](generated/golang/math/log10.h))| ✔️ |
| $(ImportDir)/math/log_asm.go | ✔️ ([cpp](generated/golang/math/log_asm.cpp), [h](generated/golang/math/log_asm.h))| ✔️ |
| $(ImportDir)/math/modf.go | ✔️ ([cpp](generated/golang/math/modf.cpp), [h](generated/golang/math/modf.h))| ✔️ |
| $(ImportDir)/math/pow.go | ✔️ ([cpp](generated/golang/math/pow.cpp), [h](generated/golang/math/pow.h))| ✔️ |
| $(ImportDir)/math/rand/exp.go | ✔️ ([cpp](generated/golang/math/rand/exp.cpp), [h](generated/golang/math/rand/exp.h))| ✔️ |
| $(ImportDir)/math/rand/normal.go | ✔️ ([cpp](generated/golang/math/rand/normal.cpp), [h](generated/golang/math/rand/normal.h))| ✔️ |
| $(ImportDir)/math/rand/rand.go | ✔️ ([cpp](generated/golang/math/rand/rand.cpp), [h](generated/golang/math/rand/rand.h))| ✔️ |
| $(ImportDir)/math/rand/rng.go | ✔️ ([cpp](generated/golang/math/rand/rng.cpp), [h](generated/golang/math/rand/rng.h))| ✔️ |
| $(ImportDir)/math/signbit.go | ✔️ ([cpp](generated/golang/math/signbit.cpp), [h](generated/golang/math/signbit.h))| ✔️ |
| $(ImportDir)/math/sqrt.go | ✔️ ([cpp](generated/golang/math/sqrt.cpp), [h](generated/golang/math/sqrt.h))| ❌ |
| $(ImportDir)/math/stubs.go | ✔️ ([cpp](generated/golang/math/stubs.cpp), [h](generated/golang/math/stubs.h))| ✔️ |
| $(ImportDir)/math/unsafe.go | ✔️ ([cpp](generated/golang/math/unsafe.cpp), [h](generated/golang/math/unsafe.h))| ✔️ |
| $(ImportDir)/os/dir.go | ✔️ ([cpp](generated/golang/os/dir.cpp), [h](generated/golang/os/dir.h))| ❌ |
| $(ImportDir)/os/dir_windows.go | ✔️ ([cpp](generated/golang/os/dir_windows.cpp), [h](generated/golang/os/dir_windows.h))| ❌ |
| $(ImportDir)/os/env.go | ✔️ ([cpp](generated/golang/os/env.cpp), [h](generated/golang/os/env.h))| ✔️ |
| $(ImportDir)/os/error.go | ✔️ ([cpp](generated/golang/os/error.cpp), [h](generated/golang/os/error.h))| ❌ |
| $(ImportDir)/os/error_errno.go | ✔️ ([cpp](generated/golang/os/error_errno.cpp), [h](generated/golang/os/error_errno.h))| ❌ |
| $(ImportDir)/os/exec.go | ✔️ ([cpp](generated/golang/os/exec.cpp), [h](generated/golang/os/exec.h))| ❌ |
| $(ImportDir)/os/exec/exec.go | ✔️ ([cpp](generated/golang/os/exec/exec.cpp), [h](generated/golang/os/exec/exec.h))| ❌ |
| $(ImportDir)/os/exec/exec_windows.go | ✔️ ([cpp](generated/golang/os/exec/exec_windows.cpp), [h](generated/golang/os/exec/exec_windows.h))| ❌ |
| $(ImportDir)/os/exec/lookpath.go | ✔️ ([cpp](generated/golang/os/exec/lookpath.cpp), [h](generated/golang/os/exec/lookpath.h))| ✔️ |
| $(ImportDir)/os/exec/lp_windows.go | ✔️ ([cpp](generated/golang/os/exec/lp_windows.cpp), [h](generated/golang/os/exec/lp_windows.h))| ❌ |
| $(ImportDir)/os/exec_posix.go | ✔️ ([cpp](generated/golang/os/exec_posix.cpp), [h](generated/golang/os/exec_posix.h))| ❌ |
| $(ImportDir)/os/exec_windows.go | ✔️ ([cpp](generated/golang/os/exec_windows.cpp), [h](generated/golang/os/exec_windows.h))| ❌ |
| $(ImportDir)/os/executable.go | ✔️ ([cpp](generated/golang/os/executable.cpp), [h](generated/golang/os/executable.h))| ❌ |
| $(ImportDir)/os/executable_windows.go | ✔️ ([cpp](generated/golang/os/executable_windows.cpp), [h](generated/golang/os/executable_windows.h))| ❌ |
| $(ImportDir)/os/file.go | ✔️ ([cpp](generated/golang/os/file.cpp), [h](generated/golang/os/file.h))| ❌ |
| $(ImportDir)/os/file_posix.go | ✔️ ([cpp](generated/golang/os/file_posix.cpp), [h](generated/golang/os/file_posix.h))| ❌ |
| $(ImportDir)/os/file_windows.go | ✔️ ([cpp](generated/golang/os/file_windows.cpp), [h](generated/golang/os/file_windows.h))| ❌ |
| $(ImportDir)/os/getwd.go | ✔️ ([cpp](generated/golang/os/getwd.cpp), [h](generated/golang/os/getwd.h))| ❌ |
| $(ImportDir)/os/path.go | ✔️ ([cpp](generated/golang/os/path.cpp), [h](generated/golang/os/path.h))| ❌ |
| $(ImportDir)/os/path_windows.go | ✔️ ([cpp](generated/golang/os/path_windows.cpp), [h](generated/golang/os/path_windows.h))| ❌ |
| $(ImportDir)/os/pidfd_other.go | ✔️ ([cpp](generated/golang/os/pidfd_other.cpp), [h](generated/golang/os/pidfd_other.h))| ❌ |
| $(ImportDir)/os/proc.go | ✔️ ([cpp](generated/golang/os/proc.cpp), [h](generated/golang/os/proc.h))| ❌ |
| $(ImportDir)/os/rawconn.go | ✔️ ([cpp](generated/golang/os/rawconn.cpp), [h](generated/golang/os/rawconn.h))| ❌ |
| $(ImportDir)/os/removeall_at.go | ✔️ ([cpp](generated/golang/os/removeall_at.cpp), [h](generated/golang/os/removeall_at.h))| ❌ |
| $(ImportDir)/os/removeall_windows.go | ✔️ ([cpp](generated/golang/os/removeall_windows.cpp), [h](generated/golang/os/removeall_windows.h))| ❌ |
| $(ImportDir)/os/root.go | ✔️ ([cpp](generated/golang/os/root.cpp), [h](generated/golang/os/root.h))| ❌ |
| $(ImportDir)/os/root_openat.go | ✔️ ([cpp](generated/golang/os/root_openat.cpp), [h](generated/golang/os/root_openat.h))| ❌ |
| $(ImportDir)/os/root_windows.go | ✔️ ([cpp](generated/golang/os/root_windows.cpp), [h](generated/golang/os/root_windows.h))| ❌ |
| $(ImportDir)/os/stat.go | ✔️ ([cpp](generated/golang/os/stat.cpp), [h](generated/golang/os/stat.h))| ❌ |
| $(ImportDir)/os/stat_windows.go | ✔️ ([cpp](generated/golang/os/stat_windows.cpp), [h](generated/golang/os/stat_windows.h))| ❌ |
| $(ImportDir)/os/sticky_notbsd.go | ✔️ ([cpp](generated/golang/os/sticky_notbsd.cpp), [h](generated/golang/os/sticky_notbsd.h))| ✔️ |
| $(ImportDir)/os/tempfile.go | ✔️ ([cpp](generated/golang/os/tempfile.cpp), [h](generated/golang/os/tempfile.h))| ❌ |
| $(ImportDir)/os/types.go | ✔️ ([cpp](generated/golang/os/types.cpp), [h](generated/golang/os/types.h))| ❌ |
| $(ImportDir)/os/types_windows.go | ✔️ ([cpp](generated/golang/os/types_windows.cpp), [h](generated/golang/os/types_windows.h))| ❌ |
| $(ImportDir)/os/zero_copy_stub.go | ✔️ ([cpp](generated/golang/os/zero_copy_stub.cpp), [h](generated/golang/os/zero_copy_stub.h))| ❌ |
| $(ImportDir)/path/filepath/path.go | ✔️ ([cpp](generated/golang/path/filepath/path.cpp), [h](generated/golang/path/filepath/path.h))| ❌ |
| $(ImportDir)/path/filepath/path_windows.go | ✔️ ([cpp](generated/golang/path/filepath/path_windows.cpp), [h](generated/golang/path/filepath/path_windows.h))| ❌ |
| $(ImportDir)/path/filepath/symlink.go | ✔️ ([cpp](generated/golang/path/filepath/symlink.cpp), [h](generated/golang/path/filepath/symlink.h))| ❌ |
| $(ImportDir)/path/filepath/symlink_windows.go | ✔️ ([cpp](generated/golang/path/filepath/symlink_windows.cpp), [h](generated/golang/path/filepath/symlink_windows.h))| ❌ |
| $(ImportDir)/path/path.go | ✔️ ([cpp](generated/golang/path/path.cpp), [h](generated/golang/path/path.h))| ✔️ |
| $(ImportDir)/reflect/abi.go | ✔️ ([cpp](generated/golang/reflect/abi.cpp), [h](generated/golang/reflect/abi.h))| ❌ |
| $(ImportDir)/reflect/deepequal.go | ✔️ ([cpp](generated/golang/reflect/deepequal.cpp), [h](generated/golang/reflect/deepequal.h))| ❌ |
| $(ImportDir)/reflect/float32reg_generic.go | ✔️ ([cpp](generated/golang/reflect/float32reg_generic.cpp), [h](generated/golang/reflect/float32reg_generic.h))| ✔️ |
| $(ImportDir)/reflect/makefunc.go | ✔️ ([cpp](generated/golang/reflect/makefunc.cpp), [h](generated/golang/reflect/makefunc.h))| ❌ |
| $(ImportDir)/reflect/map.go | ✔️ ([cpp](generated/golang/reflect/map.cpp), [h](generated/golang/reflect/map.h))| ❌ |
| $(ImportDir)/reflect/type.go | ✔️ ([cpp](generated/golang/reflect/type.cpp), [h](generated/golang/reflect/type.h))| ❌ |
| $(ImportDir)/reflect/value.go | ✔️ ([cpp](generated/golang/reflect/value.cpp), [h](generated/golang/reflect/value.h))| ❌ |
| $(ImportDir)/regexp/backtrack.go | ✔️ ([cpp](generated/golang/regexp/backtrack.cpp), [h](generated/golang/regexp/backtrack.h))| ❌ |
| $(ImportDir)/regexp/exec.go | ✔️ ([cpp](generated/golang/regexp/exec.cpp), [h](generated/golang/regexp/exec.h))| ❌ |
| $(ImportDir)/regexp/onepass.go | ✔️ ([cpp](generated/golang/regexp/onepass.cpp), [h](generated/golang/regexp/onepass.h))| ❌ |
| $(ImportDir)/regexp/regexp.go | ✔️ ([cpp](generated/golang/regexp/regexp.cpp), [h](generated/golang/regexp/regexp.h))| ❌ |
| $(ImportDir)/regexp/syntax/compile.go | ✔️ ([cpp](generated/golang/regexp/syntax/compile.cpp), [h](generated/golang/regexp/syntax/compile.h))| ❌ |
| $(ImportDir)/regexp/syntax/parse.go | ✔️ ([cpp](generated/golang/regexp/syntax/parse.cpp), [h](generated/golang/regexp/syntax/parse.h))| ❌ |
| $(ImportDir)/regexp/syntax/perl_groups.go | ✔️ ([cpp](generated/golang/regexp/syntax/perl_groups.cpp), [h](generated/golang/regexp/syntax/perl_groups.h))| ✔️ |
| $(ImportDir)/regexp/syntax/prog.go | ✔️ ([cpp](generated/golang/regexp/syntax/prog.cpp), [h](generated/golang/regexp/syntax/prog.h))| ❌ |
| $(ImportDir)/regexp/syntax/regexp.go | ✔️ ([cpp](generated/golang/regexp/syntax/regexp.cpp), [h](generated/golang/regexp/syntax/regexp.h))| ❌ |
| $(ImportDir)/regexp/syntax/simplify.go | ✔️ ([cpp](generated/golang/regexp/syntax/simplify.cpp), [h](generated/golang/regexp/syntax/simplify.h))| ✔️ |
| $(ImportDir)/runtime/alg.go | ✔️ ([cpp](generated/golang/runtime/alg.cpp), [h](generated/golang/runtime/alg.h))| ❌ |
| $(ImportDir)/runtime/arena.go | ✔️ ([cpp](generated/golang/runtime/arena.cpp), [h](generated/golang/runtime/arena.h))| ❌ |
| $(ImportDir)/runtime/asan0.go | ✔️ ([cpp](generated/golang/runtime/asan0.cpp), [h](generated/golang/runtime/asan0.h))| ❌ |
| $(ImportDir)/runtime/atomic_pointer.go | ✔️ ([cpp](generated/golang/runtime/atomic_pointer.cpp), [h](generated/golang/runtime/atomic_pointer.h))| ❌ |
| $(ImportDir)/runtime/auxv_none.go | ✔️ ([cpp](generated/golang/runtime/auxv_none.cpp), [h](generated/golang/runtime/auxv_none.h))| ✔️ |
| $(ImportDir)/runtime/cgo.go | ✔️ ([cpp](generated/golang/runtime/cgo.cpp), [h](generated/golang/runtime/cgo.h))| ❌ |
| $(ImportDir)/runtime/cgocall.go | ✔️ ([cpp](generated/golang/runtime/cgocall.cpp), [h](generated/golang/runtime/cgocall.h))| ❌ |
| $(ImportDir)/runtime/cgocheck.go | ✔️ ([cpp](generated/golang/runtime/cgocheck.cpp), [h](generated/golang/runtime/cgocheck.h))| ❌ |
| $(ImportDir)/runtime/cgroup_stubs.go | ✔️ ([cpp](generated/golang/runtime/cgroup_stubs.cpp), [h](generated/golang/runtime/cgroup_stubs.h))| ❌ |
| $(ImportDir)/runtime/chan.go | ✔️ ([cpp](generated/golang/runtime/chan.cpp), [h](generated/golang/runtime/chan.h))| ❌ |
| $(ImportDir)/runtime/compiler.go | ✔️ ([cpp](generated/golang/runtime/compiler.cpp), [h](generated/golang/runtime/compiler.h))| ✔️ |
| $(ImportDir)/runtime/coro.go | ✔️ ([cpp](generated/golang/runtime/coro.cpp), [h](generated/golang/runtime/coro.h))| ❌ |
| $(ImportDir)/runtime/cpuflags.go | ✔️ ([cpp](generated/golang/runtime/cpuflags.cpp), [h](generated/golang/runtime/cpuflags.h))| ❌ |
| $(ImportDir)/runtime/cpuprof.go | ✔️ ([cpp](generated/golang/runtime/cpuprof.cpp), [h](generated/golang/runtime/cpuprof.h))| ❌ |
| $(ImportDir)/runtime/cputicks.go | ✔️ ([cpp](generated/golang/runtime/cputicks.cpp), [h](generated/golang/runtime/cputicks.h))| ✔️ |
| $(ImportDir)/runtime/debug.go | ✔️ ([cpp](generated/golang/runtime/debug.cpp), [h](generated/golang/runtime/debug.h))| ❌ |
| $(ImportDir)/runtime/debuglog.go | ✔️ ([cpp](generated/golang/runtime/debuglog.cpp), [h](generated/golang/runtime/debuglog.h))| ❌ |
| $(ImportDir)/runtime/debuglog_off.go | ✔️ ([cpp](generated/golang/runtime/debuglog_off.cpp), [h](generated/golang/runtime/debuglog_off.h))| ✔️ |
| $(ImportDir)/runtime/env_posix.go | ✔️ ([cpp](generated/golang/runtime/env_posix.cpp), [h](generated/golang/runtime/env_posix.h))| ❌ |
| $(ImportDir)/runtime/error.go | ✔️ ([cpp](generated/golang/runtime/error.cpp), [h](generated/golang/runtime/error.h))| ❌ |
| $(ImportDir)/runtime/extern.go | ✔️ ([cpp](generated/golang/runtime/extern.cpp), [h](generated/golang/runtime/extern.h))| ❌ |
| $(ImportDir)/runtime/fastlog2.go | ✔️ ([cpp](generated/golang/runtime/fastlog2.cpp), [h](generated/golang/runtime/fastlog2.h))| ✔️ |
| $(ImportDir)/runtime/fastlog2table.go | ✔️ ([cpp](generated/golang/runtime/fastlog2table.cpp), [h](generated/golang/runtime/fastlog2table.h))| ✔️ |
| $(ImportDir)/runtime/fds_nonunix.go | ✔️ ([cpp](generated/golang/runtime/fds_nonunix.cpp), [h](generated/golang/runtime/fds_nonunix.h))| ✔️ |
| $(ImportDir)/runtime/float.go | ✔️ ([cpp](generated/golang/runtime/float.cpp), [h](generated/golang/runtime/float.h))| ❌ |
| $(ImportDir)/runtime/hexdump.go | ✔️ ([cpp](generated/golang/runtime/hexdump.cpp), [h](generated/golang/runtime/hexdump.h))| ❌ |
| $(ImportDir)/runtime/histogram.go | ✔️ ([cpp](generated/golang/runtime/histogram.cpp), [h](generated/golang/runtime/histogram.h))| ❌ |
| $(ImportDir)/runtime/iface.go | ✔️ ([cpp](generated/golang/runtime/iface.cpp), [h](generated/golang/runtime/iface.h))| ❌ |
| $(ImportDir)/runtime/lfstack.go | ✔️ ([cpp](generated/golang/runtime/lfstack.cpp), [h](generated/golang/runtime/lfstack.h))| ❌ |
| $(ImportDir)/runtime/list_manual.go | ✔️ ([cpp](generated/golang/runtime/list_manual.cpp), [h](generated/golang/runtime/list_manual.h))| ❌ |
| $(ImportDir)/runtime/lock_sema.go | ✔️ ([cpp](generated/golang/runtime/lock_sema.cpp), [h](generated/golang/runtime/lock_sema.h))| ❌ |
| $(ImportDir)/runtime/lock_spinbit.go | ✔️ ([cpp](generated/golang/runtime/lock_spinbit.cpp), [h](generated/golang/runtime/lock_spinbit.h))| ❌ |
| $(ImportDir)/runtime/lockrank.go | ✔️ ([cpp](generated/golang/runtime/lockrank.cpp), [h](generated/golang/runtime/lockrank.h))| ✔️ |
| $(ImportDir)/runtime/lockrank_off.go | ✔️ ([cpp](generated/golang/runtime/lockrank_off.cpp), [h](generated/golang/runtime/lockrank_off.h))| ❌ |
| $(ImportDir)/runtime/malloc.go | ✔️ ([cpp](generated/golang/runtime/malloc.cpp), [h](generated/golang/runtime/malloc.h))| ❌ |
| $(ImportDir)/runtime/malloc_generated.go | ✔️ ([cpp](generated/golang/runtime/malloc_generated.cpp), [h](generated/golang/runtime/malloc_generated.h))| ❌ |
| $(ImportDir)/runtime/malloc_stubs.go | ✔️ ([cpp](generated/golang/runtime/malloc_stubs.cpp), [h](generated/golang/runtime/malloc_stubs.h))| ❌ |
| $(ImportDir)/runtime/malloc_tables_generated.go | ✔️ ([cpp](generated/golang/runtime/malloc_tables_generated.cpp), [h](generated/golang/runtime/malloc_tables_generated.h))| ❌ |
| $(ImportDir)/runtime/map.go | ✔️ ([cpp](generated/golang/runtime/map.cpp), [h](generated/golang/runtime/map.h))| ❌ |
| $(ImportDir)/runtime/map_faststr.go | ✔️ ([cpp](generated/golang/runtime/map_faststr.cpp), [h](generated/golang/runtime/map_faststr.h))| ✔️ |
| $(ImportDir)/runtime/mbarrier.go | ✔️ ([cpp](generated/golang/runtime/mbarrier.cpp), [h](generated/golang/runtime/mbarrier.h))| ❌ |
| $(ImportDir)/runtime/mbitmap.go | ✔️ ([cpp](generated/golang/runtime/mbitmap.cpp), [h](generated/golang/runtime/mbitmap.h))| ❌ |
| $(ImportDir)/runtime/mcache.go | ✔️ ([cpp](generated/golang/runtime/mcache.cpp), [h](generated/golang/runtime/mcache.h))| ❌ |
| $(ImportDir)/runtime/mcentral.go | ✔️ ([cpp](generated/golang/runtime/mcentral.cpp), [h](generated/golang/runtime/mcentral.h))| ❌ |
| $(ImportDir)/runtime/mcheckmark.go | ✔️ ([cpp](generated/golang/runtime/mcheckmark.cpp), [h](generated/golang/runtime/mcheckmark.h))| ❌ |
| $(ImportDir)/runtime/mcleanup.go | ✔️ ([cpp](generated/golang/runtime/mcleanup.cpp), [h](generated/golang/runtime/mcleanup.h))| ❌ |
| $(ImportDir)/runtime/mem.go | ✔️ ([cpp](generated/golang/runtime/mem.cpp), [h](generated/golang/runtime/mem.h))| ❌ |
| $(ImportDir)/runtime/mem_nonsbrk.go | ✔️ ([cpp](generated/golang/runtime/mem_nonsbrk.cpp), [h](generated/golang/runtime/mem_nonsbrk.h))| ✔️ |
| $(ImportDir)/runtime/mem_windows.go | ✔️ ([cpp](generated/golang/runtime/mem_windows.cpp), [h](generated/golang/runtime/mem_windows.h))| ❌ |
| $(ImportDir)/runtime/metrics.go | ✔️ ([cpp](generated/golang/runtime/metrics.cpp), [h](generated/golang/runtime/metrics.h))| ❌ |
| $(ImportDir)/runtime/mfinal.go | ✔️ ([cpp](generated/golang/runtime/mfinal.cpp), [h](generated/golang/runtime/mfinal.h))| ❌ |
| $(ImportDir)/runtime/mfixalloc.go | ✔️ ([cpp](generated/golang/runtime/mfixalloc.cpp), [h](generated/golang/runtime/mfixalloc.h))| ❌ |
| $(ImportDir)/runtime/mgc.go | ✔️ ([cpp](generated/golang/runtime/mgc.cpp), [h](generated/golang/runtime/mgc.h))| ❌ |
| $(ImportDir)/runtime/mgclimit.go | ✔️ ([cpp](generated/golang/runtime/mgclimit.cpp), [h](generated/golang/runtime/mgclimit.h))| ❌ |
| $(ImportDir)/runtime/mgcmark.go | ✔️ ([cpp](generated/golang/runtime/mgcmark.cpp), [h](generated/golang/runtime/mgcmark.h))| ❌ |
| $(ImportDir)/runtime/mgcmark_greenteagc.go | ✔️ ([cpp](generated/golang/runtime/mgcmark_greenteagc.cpp), [h](generated/golang/runtime/mgcmark_greenteagc.h))| ❌ |
| $(ImportDir)/runtime/mgcpacer.go | ✔️ ([cpp](generated/golang/runtime/mgcpacer.cpp), [h](generated/golang/runtime/mgcpacer.h))| ❌ |
| $(ImportDir)/runtime/mgcscavenge.go | ✔️ ([cpp](generated/golang/runtime/mgcscavenge.cpp), [h](generated/golang/runtime/mgcscavenge.h))| ❌ |
| $(ImportDir)/runtime/mgcstack.go | ✔️ ([cpp](generated/golang/runtime/mgcstack.cpp), [h](generated/golang/runtime/mgcstack.h))| ❌ |
| $(ImportDir)/runtime/mgcsweep.go | ✔️ ([cpp](generated/golang/runtime/mgcsweep.cpp), [h](generated/golang/runtime/mgcsweep.h))| ❌ |
| $(ImportDir)/runtime/mgcwork.go | ✔️ ([cpp](generated/golang/runtime/mgcwork.cpp), [h](generated/golang/runtime/mgcwork.h))| ❌ |
| $(ImportDir)/runtime/mheap.go | ✔️ ([cpp](generated/golang/runtime/mheap.cpp), [h](generated/golang/runtime/mheap.h))| ❌ |
| $(ImportDir)/runtime/mpagealloc.go | ✔️ ([cpp](generated/golang/runtime/mpagealloc.cpp), [h](generated/golang/runtime/mpagealloc.h))| ❌ |
| $(ImportDir)/runtime/mpagealloc_64bit.go | ✔️ ([cpp](generated/golang/runtime/mpagealloc_64bit.cpp), [h](generated/golang/runtime/mpagealloc_64bit.h))| ❌ |
| $(ImportDir)/runtime/mpagecache.go | ✔️ ([cpp](generated/golang/runtime/mpagecache.cpp), [h](generated/golang/runtime/mpagecache.h))| ❌ |
| $(ImportDir)/runtime/mpallocbits.go | ✔️ ([cpp](generated/golang/runtime/mpallocbits.cpp), [h](generated/golang/runtime/mpallocbits.h))| ❌ |
| $(ImportDir)/runtime/mprof.go | ✔️ ([cpp](generated/golang/runtime/mprof.cpp), [h](generated/golang/runtime/mprof.h))| ❌ |
| $(ImportDir)/runtime/mranges.go | ✔️ ([cpp](generated/golang/runtime/mranges.cpp), [h](generated/golang/runtime/mranges.h))| ❌ |
| $(ImportDir)/runtime/msan0.go | ✔️ ([cpp](generated/golang/runtime/msan0.cpp), [h](generated/golang/runtime/msan0.h))| ❌ |
| $(ImportDir)/runtime/msize.go | ✔️ ([cpp](generated/golang/runtime/msize.cpp), [h](generated/golang/runtime/msize.h))| ❌ |
| $(ImportDir)/runtime/mspanset.go | ✔️ ([cpp](generated/golang/runtime/mspanset.cpp), [h](generated/golang/runtime/mspanset.h))| ❌ |
| $(ImportDir)/runtime/mstats.go | ✔️ ([cpp](generated/golang/runtime/mstats.cpp), [h](generated/golang/runtime/mstats.h))| ❌ |
| $(ImportDir)/runtime/mwbbuf.go | ✔️ ([cpp](generated/golang/runtime/mwbbuf.cpp), [h](generated/golang/runtime/mwbbuf.h))| ❌ |
| $(ImportDir)/runtime/netpoll.go | ✔️ ([cpp](generated/golang/runtime/netpoll.cpp), [h](generated/golang/runtime/netpoll.h))| ❌ |
| $(ImportDir)/runtime/netpoll_windows.go | ✔️ ([cpp](generated/golang/runtime/netpoll_windows.cpp), [h](generated/golang/runtime/netpoll_windows.h))| ❌ |
| $(ImportDir)/runtime/note_other.go | ✔️ ([cpp](generated/golang/runtime/note_other.cpp), [h](generated/golang/runtime/note_other.h))| ✔️ |
| $(ImportDir)/runtime/os_nonopenbsd.go | ✔️ ([cpp](generated/golang/runtime/os_nonopenbsd.cpp), [h](generated/golang/runtime/os_nonopenbsd.h))| ❌ |
| $(ImportDir)/runtime/os_windows.go | ✔️ ([cpp](generated/golang/runtime/os_windows.cpp), [h](generated/golang/runtime/os_windows.h))| ❌ |
| $(ImportDir)/runtime/panic.go | ✔️ ([cpp](generated/golang/runtime/panic.cpp), [h](generated/golang/runtime/panic.h))| ❌ |
| $(ImportDir)/runtime/pinner.go | ✔️ ([cpp](generated/golang/runtime/pinner.cpp), [h](generated/golang/runtime/pinner.h))| ❌ |
| $(ImportDir)/runtime/plugin.go | ✔️ ([cpp](generated/golang/runtime/plugin.cpp), [h](generated/golang/runtime/plugin.h))| ❌ |
| $(ImportDir)/runtime/preempt.go | ✔️ ([cpp](generated/golang/runtime/preempt.cpp), [h](generated/golang/runtime/preempt.h))| ❌ |
| $(ImportDir)/runtime/preempt_amd64.go | ✔️ ([cpp](generated/golang/runtime/preempt_amd64.cpp), [h](generated/golang/runtime/preempt_amd64.h))| ✔️ |
| $(ImportDir)/runtime/preempt_xreg.go | ✔️ ([cpp](generated/golang/runtime/preempt_xreg.cpp), [h](generated/golang/runtime/preempt_xreg.h))| ❌ |
| $(ImportDir)/runtime/print.go | ✔️ ([cpp](generated/golang/runtime/print.cpp), [h](generated/golang/runtime/print.h))| ❌ |
| $(ImportDir)/runtime/proc.go | ✔️ ([cpp](generated/golang/runtime/proc.cpp), [h](generated/golang/runtime/proc.h))| ❌ |
| $(ImportDir)/runtime/profbuf.go | ✔️ ([cpp](generated/golang/runtime/profbuf.cpp), [h](generated/golang/runtime/profbuf.h))| ❌ |
| $(ImportDir)/runtime/proflabel.go | ✔️ ([cpp](generated/golang/runtime/proflabel.cpp), [h](generated/golang/runtime/proflabel.h))| ❌ |
| $(ImportDir)/runtime/race0.go | ✔️ ([cpp](generated/golang/runtime/race0.cpp), [h](generated/golang/runtime/race0.h))| ❌ |
| $(ImportDir)/runtime/rand.go | ✔️ ([cpp](generated/golang/runtime/rand.cpp), [h](generated/golang/runtime/rand.h))| ❌ |
| $(ImportDir)/runtime/runtime.go | ✔️ ([cpp](generated/golang/runtime/runtime.cpp), [h](generated/golang/runtime/runtime.h))| ❌ |
| $(ImportDir)/runtime/runtime1.go | ✔️ ([cpp](generated/golang/runtime/runtime1.cpp), [h](generated/golang/runtime/runtime1.h))| ❌ |
| $(ImportDir)/runtime/runtime2.go | ✔️ ([cpp](generated/golang/runtime/runtime2.cpp), [h](generated/golang/runtime/runtime2.h))| ❌ |
| $(ImportDir)/runtime/rwmutex.go | ✔️ ([cpp](generated/golang/runtime/rwmutex.cpp), [h](generated/golang/runtime/rwmutex.h))| ❌ |
| $(ImportDir)/runtime/secret_asm.go | ✔️ ([cpp](generated/golang/runtime/secret_asm.cpp), [h](generated/golang/runtime/secret_asm.h))| ✔️ |
| $(ImportDir)/runtime/secret_nosecret.go | ✔️ ([cpp](generated/golang/runtime/secret_nosecret.cpp), [h](generated/golang/runtime/secret_nosecret.h))| ✔️ |
| $(ImportDir)/runtime/security_nonunix.go | ✔️ ([cpp](generated/golang/runtime/security_nonunix.cpp), [h](generated/golang/runtime/security_nonunix.h))| ✔️ |
| $(ImportDir)/runtime/select.go | ✔️ ([cpp](generated/golang/runtime/select.cpp), [h](generated/golang/runtime/select.h))| ❌ |
| $(ImportDir)/runtime/sema.go | ✔️ ([cpp](generated/golang/runtime/sema.cpp), [h](generated/golang/runtime/sema.h))| ❌ |
| $(ImportDir)/runtime/signal_windows.go | ✔️ ([cpp](generated/golang/runtime/signal_windows.cpp), [h](generated/golang/runtime/signal_windows.h))| ❌ |
| $(ImportDir)/runtime/signal_windows_amd64.go | ✔️ ([cpp](generated/golang/runtime/signal_windows_amd64.cpp), [h](generated/golang/runtime/signal_windows_amd64.h))| ❌ |
| $(ImportDir)/runtime/sigqueue.go | ✔️ ([cpp](generated/golang/runtime/sigqueue.cpp), [h](generated/golang/runtime/sigqueue.h))| ❌ |
| $(ImportDir)/runtime/sigqueue_note.go | ✔️ ([cpp](generated/golang/runtime/sigqueue_note.cpp), [h](generated/golang/runtime/sigqueue_note.h))| ❌ |
| $(ImportDir)/runtime/slice.go | ✔️ ([cpp](generated/golang/runtime/slice.cpp), [h](generated/golang/runtime/slice.h))| ❌ |
| $(ImportDir)/runtime/stack.go | ✔️ ([cpp](generated/golang/runtime/stack.cpp), [h](generated/golang/runtime/stack.h))| ❌ |
| $(ImportDir)/runtime/stkframe.go | ✔️ ([cpp](generated/golang/runtime/stkframe.cpp), [h](generated/golang/runtime/stkframe.h))| ❌ |
| $(ImportDir)/runtime/string.go | ✔️ ([cpp](generated/golang/runtime/string.cpp), [h](generated/golang/runtime/string.h))| ❌ |
| $(ImportDir)/runtime/stubs.go | ✔️ ([cpp](generated/golang/runtime/stubs.cpp), [h](generated/golang/runtime/stubs.h))| ❌ |
| $(ImportDir)/runtime/stubs3.go | ✔️ ([cpp](generated/golang/runtime/stubs3.cpp), [h](generated/golang/runtime/stubs3.h))| ✔️ |
| $(ImportDir)/runtime/stubs_amd64.go | ✔️ ([cpp](generated/golang/runtime/stubs_amd64.cpp), [h](generated/golang/runtime/stubs_amd64.h))| ✔️ |
| $(ImportDir)/runtime/stubs_nonlinux.go | ✔️ ([cpp](generated/golang/runtime/stubs_nonlinux.cpp), [h](generated/golang/runtime/stubs_nonlinux.h))| ✔️ |
| $(ImportDir)/runtime/stubs_nonwasm.go | ✔️ ([cpp](generated/golang/runtime/stubs_nonwasm.cpp), [h](generated/golang/runtime/stubs_nonwasm.h))| ✔️ |
| $(ImportDir)/runtime/symtab.go | ✔️ ([cpp](generated/golang/runtime/symtab.cpp), [h](generated/golang/runtime/symtab.h))| ❌ |
| $(ImportDir)/runtime/symtabinl.go | ✔️ ([cpp](generated/golang/runtime/symtabinl.cpp), [h](generated/golang/runtime/symtabinl.h))| ❌ |
| $(ImportDir)/runtime/synctest.go | ✔️ ([cpp](generated/golang/runtime/synctest.cpp), [h](generated/golang/runtime/synctest.h))| ❌ |
| $(ImportDir)/runtime/sys_nonppc64x.go | ✔️ ([cpp](generated/golang/runtime/sys_nonppc64x.cpp), [h](generated/golang/runtime/sys_nonppc64x.h))| ✔️ |
| $(ImportDir)/runtime/sys_x86.go | ✔️ ([cpp](generated/golang/runtime/sys_x86.cpp), [h](generated/golang/runtime/sys_x86.h))| ❌ |
| $(ImportDir)/runtime/syscall_windows.go | ✔️ ([cpp](generated/golang/runtime/syscall_windows.cpp), [h](generated/golang/runtime/syscall_windows.h))| ❌ |
| $(ImportDir)/runtime/tagptr.go | ✔️ ([cpp](generated/golang/runtime/tagptr.cpp), [h](generated/golang/runtime/tagptr.h))| ✔️ |
| $(ImportDir)/runtime/tagptr_64bit.go | ✔️ ([cpp](generated/golang/runtime/tagptr_64bit.cpp), [h](generated/golang/runtime/tagptr_64bit.h))| ❌ |
| $(ImportDir)/runtime/time.go | ✔️ ([cpp](generated/golang/runtime/time.cpp), [h](generated/golang/runtime/time.h))| ❌ |
| $(ImportDir)/runtime/time_nofake.go | ✔️ ([cpp](generated/golang/runtime/time_nofake.cpp), [h](generated/golang/runtime/time_nofake.h))| ❌ |
| $(ImportDir)/runtime/timeasm.go | ✔️ ([cpp](generated/golang/runtime/timeasm.cpp), [h](generated/golang/runtime/timeasm.h))| ✔️ |
| $(ImportDir)/runtime/tls_windows_amd64.go | ✔️ ([cpp](generated/golang/runtime/tls_windows_amd64.cpp), [h](generated/golang/runtime/tls_windows_amd64.h))| ❌ |
| $(ImportDir)/runtime/trace.go | ✔️ ([cpp](generated/golang/runtime/trace.cpp), [h](generated/golang/runtime/trace.h))| ❌ |
| $(ImportDir)/runtime/traceallocfree.go | ✔️ ([cpp](generated/golang/runtime/traceallocfree.cpp), [h](generated/golang/runtime/traceallocfree.h))| ❌ |
| $(ImportDir)/runtime/traceback.go | ✔️ ([cpp](generated/golang/runtime/traceback.cpp), [h](generated/golang/runtime/traceback.h))| ❌ |
| $(ImportDir)/runtime/tracebuf.go | ✔️ ([cpp](generated/golang/runtime/tracebuf.cpp), [h](generated/golang/runtime/tracebuf.h))| ❌ |
| $(ImportDir)/runtime/tracecpu.go | ✔️ ([cpp](generated/golang/runtime/tracecpu.cpp), [h](generated/golang/runtime/tracecpu.h))| ❌ |
| $(ImportDir)/runtime/traceevent.go | ✔️ ([cpp](generated/golang/runtime/traceevent.cpp), [h](generated/golang/runtime/traceevent.h))| ❌ |
| $(ImportDir)/runtime/tracemap.go | ✔️ ([cpp](generated/golang/runtime/tracemap.cpp), [h](generated/golang/runtime/tracemap.h))| ❌ |
| $(ImportDir)/runtime/traceregion.go | ✔️ ([cpp](generated/golang/runtime/traceregion.cpp), [h](generated/golang/runtime/traceregion.h))| ❌ |
| $(ImportDir)/runtime/traceruntime.go | ✔️ ([cpp](generated/golang/runtime/traceruntime.cpp), [h](generated/golang/runtime/traceruntime.h))| ❌ |
| $(ImportDir)/runtime/tracestack.go | ✔️ ([cpp](generated/golang/runtime/tracestack.cpp), [h](generated/golang/runtime/tracestack.h))| ❌ |
| $(ImportDir)/runtime/tracestatus.go | ✔️ ([cpp](generated/golang/runtime/tracestatus.cpp), [h](generated/golang/runtime/tracestatus.h))| ❌ |
| $(ImportDir)/runtime/tracestring.go | ✔️ ([cpp](generated/golang/runtime/tracestring.cpp), [h](generated/golang/runtime/tracestring.h))| ❌ |
| $(ImportDir)/runtime/tracetime.go | ✔️ ([cpp](generated/golang/runtime/tracetime.cpp), [h](generated/golang/runtime/tracetime.h))| ❌ |
| $(ImportDir)/runtime/tracetype.go | ✔️ ([cpp](generated/golang/runtime/tracetype.cpp), [h](generated/golang/runtime/tracetype.h))| ❌ |
| $(ImportDir)/runtime/type.go | ✔️ ([cpp](generated/golang/runtime/type.cpp), [h](generated/golang/runtime/type.h))| ❌ |
| $(ImportDir)/runtime/utf8.go | ✔️ ([cpp](generated/golang/runtime/utf8.cpp), [h](generated/golang/runtime/utf8.h))| ✔️ |
| $(ImportDir)/runtime/valgrind0.go | ✔️ ([cpp](generated/golang/runtime/valgrind0.cpp), [h](generated/golang/runtime/valgrind0.h))| ✔️ |
| $(ImportDir)/runtime/vdso_in_none.go | ✔️ ([cpp](generated/golang/runtime/vdso_in_none.cpp), [h](generated/golang/runtime/vdso_in_none.h))| ✔️ |
| $(ImportDir)/runtime/vgetrandom_unsupported.go | ✔️ ([cpp](generated/golang/runtime/vgetrandom_unsupported.cpp), [h](generated/golang/runtime/vgetrandom_unsupported.h))| ❌ |
| $(ImportDir)/runtime/write_err.go | ✔️ ([cpp](generated/golang/runtime/write_err.cpp), [h](generated/golang/runtime/write_err.h))| ❌ |
| $(ImportDir)/runtime/zcallback_windows.go | ✔️ ([cpp](generated/golang/runtime/zcallback_windows.cpp), [h](generated/golang/runtime/zcallback_windows.h))| ✔️ |
| $(ImportDir)/slices/iter.go | ✔️ ([cpp](generated/golang/slices/iter.cpp), [h](generated/golang/slices/iter.h))| ❌ |
| $(ImportDir)/slices/slices.go | ✔️ ([cpp](generated/golang/slices/slices.cpp), [h](generated/golang/slices/slices.h))| ❌ |
| $(ImportDir)/slices/sort.go | ✔️ ([cpp](generated/golang/slices/sort.cpp), [h](generated/golang/slices/sort.h))| ✔️ |
| $(ImportDir)/slices/zsortanyfunc.go | ✔️ ([cpp](generated/golang/slices/zsortanyfunc.cpp), [h](generated/golang/slices/zsortanyfunc.h))| ✔️ |
| $(ImportDir)/slices/zsortordered.go | ✔️ ([cpp](generated/golang/slices/zsortordered.cpp), [h](generated/golang/slices/zsortordered.h))| ✔️ |
| $(ImportDir)/sort/search.go | ✔️ ([cpp](generated/golang/sort/search.cpp), [h](generated/golang/sort/search.h))| ✔️ |
| $(ImportDir)/sort/slice.go | ✔️ ([cpp](generated/golang/sort/slice.cpp), [h](generated/golang/sort/slice.h))| ✔️ |
| $(ImportDir)/sort/sort.go | ✔️ ([cpp](generated/golang/sort/sort.cpp), [h](generated/golang/sort/sort.h))| ✔️ |
| $(ImportDir)/sort/zsortfunc.go | ✔️ ([cpp](generated/golang/sort/zsortfunc.cpp), [h](generated/golang/sort/zsortfunc.h))| ✔️ |
| $(ImportDir)/sort/zsortinterface.go | ✔️ ([cpp](generated/golang/sort/zsortinterface.cpp), [h](generated/golang/sort/zsortinterface.h))| ✔️ |
| $(ImportDir)/strconv/bytealg.go | ✔️ ([cpp](generated/golang/strconv/bytealg.cpp), [h](generated/golang/strconv/bytealg.h))| ✔️ |
| $(ImportDir)/strconv/isprint.go | ✔️ ([cpp](generated/golang/strconv/isprint.cpp), [h](generated/golang/strconv/isprint.h))| ✔️ |
| $(ImportDir)/strconv/number.go | ✔️ ([cpp](generated/golang/strconv/number.cpp), [h](generated/golang/strconv/number.h))| ❌ |
| $(ImportDir)/strconv/quote.go | ✔️ ([cpp](generated/golang/strconv/quote.cpp), [h](generated/golang/strconv/quote.h))| ❌ |
| $(ImportDir)/strings/builder.go | ✔️ ([cpp](generated/golang/strings/builder.cpp), [h](generated/golang/strings/builder.h))| ❌ |
| $(ImportDir)/strings/compare.go | ✔️ ([cpp](generated/golang/strings/compare.cpp), [h](generated/golang/strings/compare.h))| ✔️ |
| $(ImportDir)/strings/iter.go | ✔️ ([cpp](generated/golang/strings/iter.cpp), [h](generated/golang/strings/iter.h))| ✔️ |
| $(ImportDir)/strings/reader.go | ✔️ ([cpp](generated/golang/strings/reader.cpp), [h](generated/golang/strings/reader.h))| ✔️ |
| $(ImportDir)/strings/replace.go | ✔️ ([cpp](generated/golang/strings/replace.cpp), [h](generated/golang/strings/replace.h))| ✔️ |
| $(ImportDir)/strings/search.go | ✔️ ([cpp](generated/golang/strings/search.cpp), [h](generated/golang/strings/search.h))| ✔️ |
| $(ImportDir)/strings/strings.go | ✔️ ([cpp](generated/golang/strings/strings.cpp), [h](generated/golang/strings/strings.h))| ✔️ |
| $(ImportDir)/structs/hostlayout.go | ✔️ ([cpp](generated/golang/structs/hostlayout.cpp), [h](generated/golang/structs/hostlayout.h))| ✔️ |
| $(ImportDir)/sync/atomic/doc.go | ✔️ ([cpp](generated/golang/sync/atomic/doc.cpp), [h](generated/golang/sync/atomic/doc.h))| ✔️ |
| $(ImportDir)/sync/atomic/doc_64.go | ✔️ ([cpp](generated/golang/sync/atomic/doc_64.cpp), [h](generated/golang/sync/atomic/doc_64.h))| ✔️ |
| $(ImportDir)/sync/atomic/type.go | ✔️ ([cpp](generated/golang/sync/atomic/type.cpp), [h](generated/golang/sync/atomic/type.h))| ✔️ |
| $(ImportDir)/sync/atomic/value.go | ✔️ ([cpp](generated/golang/sync/atomic/value.cpp), [h](generated/golang/sync/atomic/value.h))| ❌ |
| $(ImportDir)/sync/cond.go | ✔️ ([cpp](generated/golang/sync/cond.cpp), [h](generated/golang/sync/cond.h))| ✔️ |
| $(ImportDir)/sync/map.go | ✔️ ([cpp](generated/golang/sync/map.cpp), [h](generated/golang/sync/map.h))| ❌ |
| $(ImportDir)/sync/mutex.go | ✔️ ([cpp](generated/golang/sync/mutex.cpp), [h](generated/golang/sync/mutex.h))| ❌ |
| $(ImportDir)/sync/once.go | ✔️ ([cpp](generated/golang/sync/once.cpp), [h](generated/golang/sync/once.h))| ✔️ |
| $(ImportDir)/sync/oncefunc.go | ✔️ ([cpp](generated/golang/sync/oncefunc.cpp), [h](generated/golang/sync/oncefunc.h))| ❌ |
| $(ImportDir)/sync/pool.go | ✔️ ([cpp](generated/golang/sync/pool.cpp), [h](generated/golang/sync/pool.h))| ❌ |
| $(ImportDir)/sync/poolqueue.go | ✔️ ([cpp](generated/golang/sync/poolqueue.cpp), [h](generated/golang/sync/poolqueue.h))| ❌ |
| $(ImportDir)/sync/runtime.go | ✔️ ([cpp](generated/golang/sync/runtime.cpp), [h](generated/golang/sync/runtime.h))| ✔️ |
| $(ImportDir)/sync/runtime2.go | ✔️ ([cpp](generated/golang/sync/runtime2.cpp), [h](generated/golang/sync/runtime2.h))| ✔️ |
| $(ImportDir)/sync/rwmutex.go | ✔️ ([cpp](generated/golang/sync/rwmutex.cpp), [h](generated/golang/sync/rwmutex.h))| ✔️ |
| $(ImportDir)/sync/waitgroup.go | ✔️ ([cpp](generated/golang/sync/waitgroup.cpp), [h](generated/golang/sync/waitgroup.h))| ✔️ |
| $(ImportDir)/syscall/dll_windows.go | ✔️ ([cpp](generated/golang/syscall/dll_windows.cpp), [h](generated/golang/syscall/dll_windows.h))| ❌ |
| $(ImportDir)/syscall/env_windows.go | ✔️ ([cpp](generated/golang/syscall/env_windows.cpp), [h](generated/golang/syscall/env_windows.h))| ❌ |
| $(ImportDir)/syscall/exec_windows.go | ✔️ ([cpp](generated/golang/syscall/exec_windows.cpp), [h](generated/golang/syscall/exec_windows.h))| ❌ |
| $(ImportDir)/syscall/net.go | ✔️ ([cpp](generated/golang/syscall/net.cpp), [h](generated/golang/syscall/net.h))| ✔️ |
| $(ImportDir)/syscall/security_windows.go | ✔️ ([cpp](generated/golang/syscall/security_windows.cpp), [h](generated/golang/syscall/security_windows.h))| ❌ |
| $(ImportDir)/syscall/syscall.go | ✔️ ([cpp](generated/golang/syscall/syscall.cpp), [h](generated/golang/syscall/syscall.h))| ❌ |
| $(ImportDir)/syscall/syscall_windows.go | ✔️ ([cpp](generated/golang/syscall/syscall_windows.cpp), [h](generated/golang/syscall/syscall_windows.h))| ❌ |
| $(ImportDir)/syscall/types_windows.go | ✔️ ([cpp](generated/golang/syscall/types_windows.cpp), [h](generated/golang/syscall/types_windows.h))| ❌ |
| $(ImportDir)/syscall/types_windows_amd64.go | ✔️ ([cpp](generated/golang/syscall/types_windows_amd64.cpp), [h](generated/golang/syscall/types_windows_amd64.h))| ❌ |
| $(ImportDir)/syscall/wtf8_windows.go | ✔️ ([cpp](generated/golang/syscall/wtf8_windows.cpp), [h](generated/golang/syscall/wtf8_windows.h))| ✔️ |
| $(ImportDir)/syscall/zerrors_windows.go | ✔️ ([cpp](generated/golang/syscall/zerrors_windows.cpp), [h](generated/golang/syscall/zerrors_windows.h))| ❌ |
| $(ImportDir)/syscall/zsyscall_windows.go | ✔️ ([cpp](generated/golang/syscall/zsyscall_windows.cpp), [h](generated/golang/syscall/zsyscall_windows.h))| ❌ |
| $(ImportDir)/time/format.go | ✔️ ([cpp](generated/golang/time/format.cpp), [h](generated/golang/time/format.h))| ❌ |
| $(ImportDir)/time/format_rfc3339.go | ✔️ ([cpp](generated/golang/time/format_rfc3339.cpp), [h](generated/golang/time/format_rfc3339.h))| ✔️ |
| $(ImportDir)/time/sleep.go | ✔️ ([cpp](generated/golang/time/sleep.cpp), [h](generated/golang/time/sleep.h))| ❌ |
| $(ImportDir)/time/sys_windows.go | ✔️ ([cpp](generated/golang/time/sys_windows.cpp), [h](generated/golang/time/sys_windows.h))| ❌ |
| $(ImportDir)/time/tick.go | ✔️ ([cpp](generated/golang/time/tick.cpp), [h](generated/golang/time/tick.h))| ❌ |
| $(ImportDir)/time/time.go | ✔️ ([cpp](generated/golang/time/time.cpp), [h](generated/golang/time/time.h))| ❌ |
| $(ImportDir)/time/zoneinfo.go | ✔️ ([cpp](generated/golang/time/zoneinfo.cpp), [h](generated/golang/time/zoneinfo.h))| ❌ |
| $(ImportDir)/time/zoneinfo_abbrs_windows.go | ✔️ ([cpp](generated/golang/time/zoneinfo_abbrs_windows.cpp), [h](generated/golang/time/zoneinfo_abbrs_windows.h))| ✔️ |
| $(ImportDir)/time/zoneinfo_goroot.go | ✔️ ([cpp](generated/golang/time/zoneinfo_goroot.cpp), [h](generated/golang/time/zoneinfo_goroot.h))| ✔️ |
| $(ImportDir)/time/zoneinfo_read.go | ✔️ ([cpp](generated/golang/time/zoneinfo_read.cpp), [h](generated/golang/time/zoneinfo_read.h))| ❌ |
| $(ImportDir)/time/zoneinfo_windows.go | ✔️ ([cpp](generated/golang/time/zoneinfo_windows.cpp), [h](generated/golang/time/zoneinfo_windows.h))| ❌ |
| $(ImportDir)/unicode/digit.go | ✔️ ([cpp](generated/golang/unicode/digit.cpp), [h](generated/golang/unicode/digit.h))| ✔️ |
| $(ImportDir)/unicode/graphic.go | ✔️ ([cpp](generated/golang/unicode/graphic.cpp), [h](generated/golang/unicode/graphic.h))| ❌ |
| $(ImportDir)/unicode/letter.go | ✔️ ([cpp](generated/golang/unicode/letter.cpp), [h](generated/golang/unicode/letter.h))| ❌ |
| $(ImportDir)/unicode/tables.go | ✔️ ([cpp](generated/golang/unicode/tables.cpp), [h](generated/golang/unicode/tables.h))| ❌ |
| $(ImportDir)/unicode/utf16/utf16.go | ✔️ ([cpp](generated/golang/unicode/utf16/utf16.cpp), [h](generated/golang/unicode/utf16/utf16.h))| ✔️ |
| $(ImportDir)/unicode/utf8/utf8.go | ✔️ ([cpp](generated/golang/unicode/utf8/utf8.cpp), [h](generated/golang/unicode/utf8/utf8.h))| ❌ |
