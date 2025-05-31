# Results on test directory

| file | cpp generate | cpp compilation | run | result diff |
| ---- | ------------ | --------------- | --- | ----------- |
| [HelloWorld.go](tests/HelloWorld.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/HelloWorld.cpp)) | ❌ |
| [TourOfGo/basics/basic-types.go](tests/TourOfGo/basics/basic-types.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/basics/basic-types.cpp)) | ❌ |
| [TourOfGo/basics/constants.go](tests/TourOfGo/basics/constants.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/basics/constants.cpp)) | ❌ |
| [TourOfGo/basics/ellipsis.go](tests/TourOfGo/basics/ellipsis.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/basics/ellipsis.cpp)) | ❌ |
| [TourOfGo/basics/exported-names.go](tests/TourOfGo/basics/exported-names.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/basics/exported-names.cpp)) | ❌ |
| [TourOfGo/basics/functions.go](tests/TourOfGo/basics/functions.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/basics/functions.cpp)) | ✔️ |
| [TourOfGo/basics/functions-continued.go](tests/TourOfGo/basics/functions-continued.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/basics/functions-continued.cpp)) | ✔️ |
| [TourOfGo/basics/imports.go](tests/TourOfGo/basics/imports.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/basics/imports.cpp)) | ❌ |
| [TourOfGo/basics/inline-values.go](tests/TourOfGo/basics/inline-values.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/basics/inline-values.cpp)) | ✔️ |
| [TourOfGo/basics/iota.go](tests/TourOfGo/basics/iota.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/basics/iota.cpp)) | ✔️ |
| [TourOfGo/basics/multiple-results.go](tests/TourOfGo/basics/multiple-results.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/basics/multiple-results.cpp)) | ✔️ |
| [TourOfGo/basics/name-conflicts.go](tests/TourOfGo/basics/name-conflicts.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/basics/name-conflicts.cpp)) | ❌ |
| [TourOfGo/basics/name-conflicts-full.go](tests/TourOfGo/basics/name-conflicts-full.go) | ✔️ | ❌ | ❌ | ❌ |
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
| [TourOfGo/concurrency/channels.go](tests/TourOfGo/concurrency/channels.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/concurrency/channels.cpp)) | ❌ |
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
| [TourOfGo/flowcontrol/exercise-loops-and-functions.go](tests/TourOfGo/flowcontrol/exercise-loops-and-functions.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/flowcontrol/exercise-loops-and-functions.cpp)) | ❌ |
| [TourOfGo/flowcontrol/for.go](tests/TourOfGo/flowcontrol/for.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/flowcontrol/for.cpp)) | ✔️ |
| [TourOfGo/flowcontrol/for-break-continue.go](tests/TourOfGo/flowcontrol/for-break-continue.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/flowcontrol/for-break-continue.cpp)) | ✔️ |
| [TourOfGo/flowcontrol/for-continued.go](tests/TourOfGo/flowcontrol/for-continued.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/flowcontrol/for-continued.cpp)) | ✔️ |
| [TourOfGo/flowcontrol/forever.go](tests/TourOfGo/flowcontrol/forever.go) | ✔️ | ✔️ | ➖ | ➖ | 
| [TourOfGo/flowcontrol/for-is-gos-while.go](tests/TourOfGo/flowcontrol/for-is-gos-while.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/flowcontrol/for-is-gos-while.cpp)) | ✔️ |
| [TourOfGo/flowcontrol/if.go](tests/TourOfGo/flowcontrol/if.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/flowcontrol/if.cpp)) | ❌ |
| [TourOfGo/flowcontrol/if-and-else.go](tests/TourOfGo/flowcontrol/if-and-else.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/flowcontrol/if-and-else.cpp)) | ❌ |
| [TourOfGo/flowcontrol/if-with-a-short-statement.go](tests/TourOfGo/flowcontrol/if-with-a-short-statement.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/flowcontrol/if-with-a-short-statement.cpp)) | ❌ |
| [TourOfGo/flowcontrol/inlined-statements-scope.go](tests/TourOfGo/flowcontrol/inlined-statements-scope.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/flowcontrol/inlined-statements-scope.cpp)) | ✔️ |
| [TourOfGo/flowcontrol/labels.go](tests/TourOfGo/flowcontrol/labels.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/flowcontrol/labels.cpp)) | ✔️ |
| [TourOfGo/flowcontrol/switch.go](tests/TourOfGo/flowcontrol/switch.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/flowcontrol/switch.cpp)) | ❌ |
| [TourOfGo/flowcontrol/switch-evaluation-order.go](tests/TourOfGo/flowcontrol/switch-evaluation-order.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/flowcontrol/switch-evaluation-order.cpp)) | ➖ | 
| [TourOfGo/flowcontrol/switch-numeric.go](tests/TourOfGo/flowcontrol/switch-numeric.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/flowcontrol/switch-numeric.cpp)) | ➖ | 
| [TourOfGo/flowcontrol/switch-with-no-condition.go](tests/TourOfGo/flowcontrol/switch-with-no-condition.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/flowcontrol/switch-with-no-condition.cpp)) | ➖ | 
| [TourOfGo/generics/generics.go](tests/TourOfGo/generics/generics.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/generics/generics.cpp)) | ✔️ |
| [TourOfGo/methods/empty-interface.go](tests/TourOfGo/methods/empty-interface.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/methods/empty-interface.cpp)) | ❌ |
| [TourOfGo/methods/errors.go](tests/TourOfGo/methods/errors.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/methods/errors.cpp)) | ❌ |
| [TourOfGo/methods/exercise-errors.go](tests/TourOfGo/methods/exercise-errors.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/methods/exercise-errors.cpp)) | ❌ |
| [TourOfGo/methods/exercise-images.go](tests/TourOfGo/methods/exercise-images.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/methods/exercise-images.cpp)) | ❌ |
| [TourOfGo/methods/exercise-reader.go](tests/TourOfGo/methods/exercise-reader.go) | ✔️ | ❌ | ❌ | ❌ |
| [TourOfGo/methods/exercise-rot-reader.go](tests/TourOfGo/methods/exercise-rot-reader.go) | ✔️ | ❌ | ❌ | ❌ |
| [TourOfGo/methods/exercise-stringer.go](tests/TourOfGo/methods/exercise-stringer.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/methods/exercise-stringer.cpp)) | ❌ |
| [TourOfGo/methods/images.go](tests/TourOfGo/methods/images.go) | ✔️ | ❌ | ❌ | ❌ |
| [TourOfGo/methods/indirection.go](tests/TourOfGo/methods/indirection.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/methods/indirection.cpp)) | ❌ |
| [TourOfGo/methods/indirection-values.go](tests/TourOfGo/methods/indirection-values.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/methods/indirection-values.cpp)) | ❌ |
| [TourOfGo/methods/inline-interface.go](tests/TourOfGo/methods/inline-interface.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/methods/inline-interface.cpp)) | ❌ |
| [TourOfGo/methods/interfaces.go](tests/TourOfGo/methods/interfaces.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/methods/interfaces.cpp)) | ❌ |
| [TourOfGo/methods/interfaces-are-satisfied-implicitly.go](tests/TourOfGo/methods/interfaces-are-satisfied-implicitly.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/methods/interfaces-are-satisfied-implicitly.cpp)) | ✔️ |
| [TourOfGo/methods/interfaces-cast.go](tests/TourOfGo/methods/interfaces-cast.go) | ✔️ | ✔️ | ❌ | ❌ |
| [TourOfGo/methods/interfaces-ordered.go](tests/TourOfGo/methods/interfaces-ordered.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/methods/interfaces-ordered.cpp)) | ❌ |
| [TourOfGo/methods/interface-values.go](tests/TourOfGo/methods/interface-values.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/methods/interface-values.cpp)) | ❌ |
| [TourOfGo/methods/interface-values-with-nil.go](tests/TourOfGo/methods/interface-values-with-nil.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/methods/interface-values-with-nil.cpp)) | ❌ |
| [TourOfGo/methods/interface-values-with-unitialized.go](tests/TourOfGo/methods/interface-values-with-unitialized.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/methods/interface-values-with-unitialized.cpp)) | ❌ |
| [TourOfGo/methods/methods.go](tests/TourOfGo/methods/methods.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/methods/methods.cpp)) | ❌ |
| [TourOfGo/methods/methods-continued.go](tests/TourOfGo/methods/methods-continued.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/methods/methods-continued.cpp)) | ❌ |
| [TourOfGo/methods/methods-funcs.go](tests/TourOfGo/methods/methods-funcs.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/methods/methods-funcs.cpp)) | ❌ |
| [TourOfGo/methods/methods-pointers.go](tests/TourOfGo/methods/methods-pointers.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/methods/methods-pointers.cpp)) | ❌ |
| [TourOfGo/methods/methods-pointers-explained.go](tests/TourOfGo/methods/methods-pointers-explained.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/methods/methods-pointers-explained.cpp)) | ❌ |
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
| [TourOfGo/moretypes/function-values.go](tests/TourOfGo/moretypes/function-values.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/moretypes/function-values.cpp)) | ❌ |
| [TourOfGo/moretypes/making-slices.go](tests/TourOfGo/moretypes/making-slices.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/moretypes/making-slices.cpp)) | ❌ |
| [TourOfGo/moretypes/map-literals.go](tests/TourOfGo/moretypes/map-literals.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/moretypes/map-literals.cpp)) | ✔️ |
| [TourOfGo/moretypes/map-literals-continued.go](tests/TourOfGo/moretypes/map-literals-continued.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/moretypes/map-literals-continued.cpp)) | ✔️ |
| [TourOfGo/moretypes/maps.go](tests/TourOfGo/moretypes/maps.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/moretypes/maps.cpp)) | ✔️ |
| [TourOfGo/moretypes/mutating-maps.go](tests/TourOfGo/moretypes/mutating-maps.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/moretypes/mutating-maps.cpp)) | ❌ |
| [TourOfGo/moretypes/nil-slices.go](tests/TourOfGo/moretypes/nil-slices.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/moretypes/nil-slices.cpp)) | ✔️ |
| [TourOfGo/moretypes/pointers.go](tests/TourOfGo/moretypes/pointers.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/moretypes/pointers.cpp)) | ✔️ |
| [TourOfGo/moretypes/range.go](tests/TourOfGo/moretypes/range.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/moretypes/range.cpp)) | ✔️ |
| [TourOfGo/moretypes/range-continued.go](tests/TourOfGo/moretypes/range-continued.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/moretypes/range-continued.cpp)) | ✔️ |
| [TourOfGo/moretypes/slice-bounds.go](tests/TourOfGo/moretypes/slice-bounds.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/moretypes/slice-bounds.cpp)) | ❌ |
| [TourOfGo/moretypes/slice-len-cap.go](tests/TourOfGo/moretypes/slice-len-cap.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/moretypes/slice-len-cap.cpp)) | ❌ |
| [TourOfGo/moretypes/slice-literals.go](tests/TourOfGo/moretypes/slice-literals.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/moretypes/slice-literals.cpp)) | ✔️ |
| [TourOfGo/moretypes/slices.go](tests/TourOfGo/moretypes/slices.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/moretypes/slices.cpp)) | ✔️ |
| [TourOfGo/moretypes/slices-of-slice.go](tests/TourOfGo/moretypes/slices-of-slice.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/moretypes/slices-of-slice.cpp)) | ✔️ |
| [TourOfGo/moretypes/slices-pointers.go](tests/TourOfGo/moretypes/slices-pointers.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/moretypes/slices-pointers.cpp)) | ✔️ |
| [TourOfGo/moretypes/struct-fields.go](tests/TourOfGo/moretypes/struct-fields.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/moretypes/struct-fields.cpp)) | ✔️ |
| [TourOfGo/moretypes/struct-fields-initializer.go](tests/TourOfGo/moretypes/struct-fields-initializer.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/moretypes/struct-fields-initializer.cpp)) | ✔️ |
| [TourOfGo/moretypes/struct-literals.go](tests/TourOfGo/moretypes/struct-literals.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/moretypes/struct-literals.cpp)) | ❌ |
| [TourOfGo/moretypes/struct-pointers.go](tests/TourOfGo/moretypes/struct-pointers.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/moretypes/struct-pointers.cpp)) | ✔️ |
| [TourOfGo/moretypes/structs.go](tests/TourOfGo/moretypes/structs.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/moretypes/structs.cpp)) | ✔️ |
| [TourOfGo/moretypes/typedef.go](tests/TourOfGo/moretypes/typedef.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/moretypes/typedef.cpp)) | ✔️ |
| [TourOfGo/welcome/hello.go](tests/TourOfGo/welcome/hello.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/welcome/hello.cpp)) | ✔️ |
| [TourOfGo/welcome/sandbox.go](tests/TourOfGo/welcome/sandbox.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/welcome/sandbox.cpp)) | ❌ |


# Conversion of imported packages
| file | cpp generate | cpp compile |
| ---- | -------------| ----------- |
| $(ImportDir)/bufio/bufio.go | ✔️ ([cpp](generated/golang/bufio/bufio.cpp), [h](generated/golang/bufio/bufio.h))| ❌ |
| $(ImportDir)/bytes/buffer.go | ✔️ ([cpp](generated/golang/bytes/buffer.cpp), [h](generated/golang/bytes/buffer.h))| ❌ |
| $(ImportDir)/bytes/bytes.go | ✔️ ([cpp](generated/golang/bytes/bytes.cpp), [h](generated/golang/bytes/bytes.h))| ❌ |
| $(ImportDir)/cmp/cmp.go | ✔️ ([cpp](generated/golang/cmp/cmp.cpp), [h](generated/golang/cmp/cmp.h))| ✔️ |
| $(ImportDir)/compress/flate/deflate.go | ✔️ ([cpp](generated/golang/compress/flate/deflate.cpp), [h](generated/golang/compress/flate/deflate.h))| ❌ |
| $(ImportDir)/compress/flate/deflatefast.go | ✔️ ([cpp](generated/golang/compress/flate/deflatefast.cpp), [h](generated/golang/compress/flate/deflatefast.h))| ❌ |
| $(ImportDir)/compress/flate/dict_decoder.go | ✔️ ([cpp](generated/golang/compress/flate/dict_decoder.cpp), [h](generated/golang/compress/flate/dict_decoder.h))| ✔️ |
| $(ImportDir)/compress/flate/huffman_bit_writer.go | ✔️ ([cpp](generated/golang/compress/flate/huffman_bit_writer.cpp), [h](generated/golang/compress/flate/huffman_bit_writer.h))| ❌ |
| $(ImportDir)/compress/flate/huffman_code.go | ✔️ ([cpp](generated/golang/compress/flate/huffman_code.cpp), [h](generated/golang/compress/flate/huffman_code.h))| ❌ |
| $(ImportDir)/compress/flate/inflate.go | ✔️ ([cpp](generated/golang/compress/flate/inflate.cpp), [h](generated/golang/compress/flate/inflate.h))| ❌ |
| $(ImportDir)/compress/flate/token.go | ✔️ ([cpp](generated/golang/compress/flate/token.cpp), [h](generated/golang/compress/flate/token.h))| ❌ |
| $(ImportDir)/compress/zlib/reader.go | ✔️ ([cpp](generated/golang/compress/zlib/reader.cpp), [h](generated/golang/compress/zlib/reader.h))| ❌ |
| $(ImportDir)/compress/zlib/writer.go | ✔️ ([cpp](generated/golang/compress/zlib/writer.cpp), [h](generated/golang/compress/zlib/writer.h))| ❌ |
| $(ImportDir)/encoding/base64/base64.go | ✔️ ([cpp](generated/golang/encoding/base64/base64.cpp), [h](generated/golang/encoding/base64/base64.h))| ❌ |
| $(ImportDir)/encoding/binary/binary.go | ✔️ ([cpp](generated/golang/encoding/binary/binary.cpp), [h](generated/golang/encoding/binary/binary.h))| ❌ |
| $(ImportDir)/encoding/binary/native_endian_little.go | ✔️ ([cpp](generated/golang/encoding/binary/native_endian_little.cpp), [h](generated/golang/encoding/binary/native_endian_little.h))| ❌ |
| $(ImportDir)/errors/errors.go | ✔️ ([cpp](generated/golang/errors/errors.cpp), [h](generated/golang/errors/errors.h))| ✔️ |
| $(ImportDir)/errors/wrap.go | ✔️ ([cpp](generated/golang/errors/wrap.cpp), [h](generated/golang/errors/wrap.h))| ❌ |
| $(ImportDir)/fmt/errors.go | ✔️ ([cpp](generated/golang/fmt/errors.cpp), [h](generated/golang/fmt/errors.h))| ❌ |
| $(ImportDir)/fmt/format.go | ✔️ ([cpp](generated/golang/fmt/format.cpp), [h](generated/golang/fmt/format.h))| ❌ |
| $(ImportDir)/fmt/print.go | ✔️ ([cpp](generated/golang/fmt/print.cpp), [h](generated/golang/fmt/print.h))| ❌ |
| $(ImportDir)/golang.org/x/tour/pic/pic.go | ✔️ ([cpp](generated/golang/golang.org/x/tour/pic/pic.cpp), [h](generated/golang/golang.org/x/tour/pic/pic.h))| ❌ |
| $(ImportDir)/golang.org/x/tour/reader/validate.go | ✔️ ([cpp](generated/golang/golang.org/x/tour/reader/validate.cpp), [h](generated/golang/golang.org/x/tour/reader/validate.h))| ❌ |
| $(ImportDir)/golang.org/x/tour/tree/tree.go | ✔️ ([cpp](generated/golang/golang.org/x/tour/tree/tree.cpp), [h](generated/golang/golang.org/x/tour/tree/tree.h))| ❌ |
| $(ImportDir)/golang.org/x/tour/wc/wc.go | ✔️ ([cpp](generated/golang/golang.org/x/tour/wc/wc.cpp), [h](generated/golang/golang.org/x/tour/wc/wc.h))| ❌ |
| $(ImportDir)/hash/adler32/adler32.go | ✔️ ([cpp](generated/golang/hash/adler32/adler32.cpp), [h](generated/golang/hash/adler32/adler32.h))| ❌ |
| $(ImportDir)/hash/crc32/crc32.go | ✔️ ([cpp](generated/golang/hash/crc32/crc32.cpp), [h](generated/golang/hash/crc32/crc32.h))| ❌ |
| $(ImportDir)/hash/crc32/crc32_amd64.go | ✔️ ([cpp](generated/golang/hash/crc32/crc32_amd64.cpp), [h](generated/golang/hash/crc32/crc32_amd64.h))| ❌ |
| $(ImportDir)/hash/crc32/crc32_generic.go | ✔️ ([cpp](generated/golang/hash/crc32/crc32_generic.cpp), [h](generated/golang/hash/crc32/crc32_generic.h))| ❌ |
| $(ImportDir)/hash/hash.go | ✔️ ([cpp](generated/golang/hash/hash.cpp), [h](generated/golang/hash/hash.h))| ✔️ |
| $(ImportDir)/image/color/color.go | ✔️ ([cpp](generated/golang/image/color/color.cpp), [h](generated/golang/image/color/color.h))| ❌ |
| $(ImportDir)/image/color/ycbcr.go | ✔️ ([cpp](generated/golang/image/color/ycbcr.cpp), [h](generated/golang/image/color/ycbcr.h))| ❌ |
| $(ImportDir)/image/format.go | ✔️ ([cpp](generated/golang/image/format.cpp), [h](generated/golang/image/format.h))| ❌ |
| $(ImportDir)/image/geom.go | ✔️ ([cpp](generated/golang/image/geom.cpp), [h](generated/golang/image/geom.h))| ❌ |
| $(ImportDir)/image/image.go | ✔️ ([cpp](generated/golang/image/image.cpp), [h](generated/golang/image/image.h))| ❌ |
| $(ImportDir)/image/png/paeth.go | ✔️ ([cpp](generated/golang/image/png/paeth.cpp), [h](generated/golang/image/png/paeth.h))| ✔️ |
| $(ImportDir)/image/png/reader.go | ✔️ ([cpp](generated/golang/image/png/reader.cpp), [h](generated/golang/image/png/reader.h))| ❌ |
| $(ImportDir)/image/png/writer.go | ✔️ ([cpp](generated/golang/image/png/writer.cpp), [h](generated/golang/image/png/writer.h))| ❌ |
| $(ImportDir)/internal/abi/abi.go | ✔️ ([cpp](generated/golang/internal/abi/abi.cpp), [h](generated/golang/internal/abi/abi.h))| ❌ |
| $(ImportDir)/internal/abi/abi_amd64.go | ✔️ ([cpp](generated/golang/internal/abi/abi_amd64.cpp), [h](generated/golang/internal/abi/abi_amd64.h))| ✔️ |
| $(ImportDir)/internal/abi/funcpc.go | ✔️ ([cpp](generated/golang/internal/abi/funcpc.cpp), [h](generated/golang/internal/abi/funcpc.h))| ✔️ |
| $(ImportDir)/internal/abi/map.go | ✔️ ([cpp](generated/golang/internal/abi/map.cpp), [h](generated/golang/internal/abi/map.h))| ✔️ |
| $(ImportDir)/internal/abi/stack.go | ✔️ ([cpp](generated/golang/internal/abi/stack.cpp), [h](generated/golang/internal/abi/stack.h))| ✔️ |
| $(ImportDir)/internal/abi/switch.go | ✔️ ([cpp](generated/golang/internal/abi/switch.cpp), [h](generated/golang/internal/abi/switch.h))| ✔️ |
| $(ImportDir)/internal/abi/symtab.go | ✔️ ([cpp](generated/golang/internal/abi/symtab.cpp), [h](generated/golang/internal/abi/symtab.h))| ✔️ |
| $(ImportDir)/internal/abi/type.go | ✔️ ([cpp](generated/golang/internal/abi/type.cpp), [h](generated/golang/internal/abi/type.h))| ❌ |
| $(ImportDir)/internal/bisect/bisect.go | ✔️ ([cpp](generated/golang/internal/bisect/bisect.cpp), [h](generated/golang/internal/bisect/bisect.h))| ❌ |
| $(ImportDir)/internal/bytealg/bytealg.go | ✔️ ([cpp](generated/golang/internal/bytealg/bytealg.cpp), [h](generated/golang/internal/bytealg/bytealg.h))| ❌ |
| $(ImportDir)/internal/bytealg/compare_native.go | ✔️ ([cpp](generated/golang/internal/bytealg/compare_native.cpp), [h](generated/golang/internal/bytealg/compare_native.h))| ✔️ |
| $(ImportDir)/internal/bytealg/count_native.go | ✔️ ([cpp](generated/golang/internal/bytealg/count_native.cpp), [h](generated/golang/internal/bytealg/count_native.h))| ✔️ |
| $(ImportDir)/internal/bytealg/index_amd64.go | ✔️ ([cpp](generated/golang/internal/bytealg/index_amd64.cpp), [h](generated/golang/internal/bytealg/index_amd64.h))| ❌ |
| $(ImportDir)/internal/bytealg/index_native.go | ✔️ ([cpp](generated/golang/internal/bytealg/index_native.cpp), [h](generated/golang/internal/bytealg/index_native.h))| ✔️ |
| $(ImportDir)/internal/bytealg/indexbyte_native.go | ✔️ ([cpp](generated/golang/internal/bytealg/indexbyte_native.cpp), [h](generated/golang/internal/bytealg/indexbyte_native.h))| ✔️ |
| $(ImportDir)/internal/bytealg/lastindexbyte_generic.go | ✔️ ([cpp](generated/golang/internal/bytealg/lastindexbyte_generic.cpp), [h](generated/golang/internal/bytealg/lastindexbyte_generic.h))| ✔️ |
| $(ImportDir)/internal/chacha8rand/chacha8.go | ✔️ ([cpp](generated/golang/internal/chacha8rand/chacha8.cpp), [h](generated/golang/internal/chacha8rand/chacha8.h))| ❌ |
| $(ImportDir)/internal/cpu/cpu.go | ✔️ ([cpp](generated/golang/internal/cpu/cpu.cpp), [h](generated/golang/internal/cpu/cpu.h))| ❌ |
| $(ImportDir)/internal/cpu/cpu_x86.go | ✔️ ([cpp](generated/golang/internal/cpu/cpu_x86.cpp), [h](generated/golang/internal/cpu/cpu_x86.h))| ❌ |
| $(ImportDir)/internal/fmtsort/sort.go | ✔️ ([cpp](generated/golang/internal/fmtsort/sort.cpp), [h](generated/golang/internal/fmtsort/sort.h))| ❌ |
| $(ImportDir)/internal/goarch/goarch.go | ✔️ ([cpp](generated/golang/internal/goarch/goarch.cpp), [h](generated/golang/internal/goarch/goarch.h))| ✔️ |
| $(ImportDir)/internal/goarch/goarch_amd64.go | ✔️ ([cpp](generated/golang/internal/goarch/goarch_amd64.cpp), [h](generated/golang/internal/goarch/goarch_amd64.h))| ❌ |
| $(ImportDir)/internal/goarch/zgoarch_amd64.go | ✔️ ([cpp](generated/golang/internal/goarch/zgoarch_amd64.cpp), [h](generated/golang/internal/goarch/zgoarch_amd64.h))| ✔️ |
| $(ImportDir)/internal/godebug/godebug.go | ✔️ ([cpp](generated/golang/internal/godebug/godebug.cpp), [h](generated/golang/internal/godebug/godebug.h))| ❌ |
| $(ImportDir)/internal/godebugs/table.go | ✔️ ([cpp](generated/golang/internal/godebugs/table.cpp), [h](generated/golang/internal/godebugs/table.h))| ❌ |
| $(ImportDir)/internal/goexperiment/exp_allocheaders_on.go | ✔️ ([cpp](generated/golang/internal/goexperiment/exp_allocheaders_on.cpp), [h](generated/golang/internal/goexperiment/exp_allocheaders_on.h))| ✔️ |
| $(ImportDir)/internal/goexperiment/exp_cgocheck2_off.go | ✔️ ([cpp](generated/golang/internal/goexperiment/exp_cgocheck2_off.cpp), [h](generated/golang/internal/goexperiment/exp_cgocheck2_off.h))| ✔️ |
| $(ImportDir)/internal/goexperiment/exp_exectracer2_on.go | ✔️ ([cpp](generated/golang/internal/goexperiment/exp_exectracer2_on.cpp), [h](generated/golang/internal/goexperiment/exp_exectracer2_on.h))| ✔️ |
| $(ImportDir)/internal/goexperiment/exp_heapminimum512kib_off.go | ✔️ ([cpp](generated/golang/internal/goexperiment/exp_heapminimum512kib_off.cpp), [h](generated/golang/internal/goexperiment/exp_heapminimum512kib_off.h))| ✔️ |
| $(ImportDir)/internal/goos/zgoos_windows.go | ✔️ ([cpp](generated/golang/internal/goos/zgoos_windows.cpp), [h](generated/golang/internal/goos/zgoos_windows.h))| ✔️ |
| $(ImportDir)/internal/itoa/itoa.go | ✔️ ([cpp](generated/golang/internal/itoa/itoa.cpp), [h](generated/golang/internal/itoa/itoa.h))| ❌ |
| $(ImportDir)/internal/poll/errno_windows.go | ✔️ ([cpp](generated/golang/internal/poll/errno_windows.cpp), [h](generated/golang/internal/poll/errno_windows.h))| ❌ |
| $(ImportDir)/internal/poll/fd.go | ✔️ ([cpp](generated/golang/internal/poll/fd.cpp), [h](generated/golang/internal/poll/fd.h))| ✔️ |
| $(ImportDir)/internal/poll/fd_fsync_windows.go | ✔️ ([cpp](generated/golang/internal/poll/fd_fsync_windows.cpp), [h](generated/golang/internal/poll/fd_fsync_windows.h))| ❌ |
| $(ImportDir)/internal/poll/fd_mutex.go | ✔️ ([cpp](generated/golang/internal/poll/fd_mutex.cpp), [h](generated/golang/internal/poll/fd_mutex.h))| ❌ |
| $(ImportDir)/internal/poll/fd_poll_runtime.go | ✔️ ([cpp](generated/golang/internal/poll/fd_poll_runtime.cpp), [h](generated/golang/internal/poll/fd_poll_runtime.h))| ❌ |
| $(ImportDir)/internal/poll/fd_posix.go | ✔️ ([cpp](generated/golang/internal/poll/fd_posix.cpp), [h](generated/golang/internal/poll/fd_posix.h))| ❌ |
| $(ImportDir)/internal/poll/fd_windows.go | ✔️ ([cpp](generated/golang/internal/poll/fd_windows.cpp), [h](generated/golang/internal/poll/fd_windows.h))| ❌ |
| $(ImportDir)/internal/race/norace.go | ✔️ ([cpp](generated/golang/internal/race/norace.cpp), [h](generated/golang/internal/race/norace.h))| ❌ |
| $(ImportDir)/internal/reflectlite/swapper.go | ✔️ ([cpp](generated/golang/internal/reflectlite/swapper.cpp), [h](generated/golang/internal/reflectlite/swapper.h))| ❌ |
| $(ImportDir)/internal/reflectlite/type.go | ✔️ ([cpp](generated/golang/internal/reflectlite/type.cpp), [h](generated/golang/internal/reflectlite/type.h))| ❌ |
| $(ImportDir)/internal/reflectlite/value.go | ✔️ ([cpp](generated/golang/internal/reflectlite/value.cpp), [h](generated/golang/internal/reflectlite/value.h))| ❌ |
| $(ImportDir)/internal/safefilepath/path.go | ✔️ ([cpp](generated/golang/internal/safefilepath/path.cpp), [h](generated/golang/internal/safefilepath/path.h))| ✔️ |
| $(ImportDir)/internal/safefilepath/path_windows.go | ✔️ ([cpp](generated/golang/internal/safefilepath/path_windows.cpp), [h](generated/golang/internal/safefilepath/path_windows.h))| ❌ |
| $(ImportDir)/internal/syscall/windows/memory_windows.go | ✔️ ([cpp](generated/golang/internal/syscall/windows/memory_windows.cpp), [h](generated/golang/internal/syscall/windows/memory_windows.h))| ✔️ |
| $(ImportDir)/internal/syscall/windows/net_windows.go | ✔️ ([cpp](generated/golang/internal/syscall/windows/net_windows.cpp), [h](generated/golang/internal/syscall/windows/net_windows.h))| ❌ |
| $(ImportDir)/internal/syscall/windows/psapi_windows.go | ✔️ ([cpp](generated/golang/internal/syscall/windows/psapi_windows.cpp), [h](generated/golang/internal/syscall/windows/psapi_windows.h))| ✔️ |
| $(ImportDir)/internal/syscall/windows/registry/key.go | ✔️ ([cpp](generated/golang/internal/syscall/windows/registry/key.cpp), [h](generated/golang/internal/syscall/windows/registry/key.h))| ❌ |
| $(ImportDir)/internal/syscall/windows/registry/syscall.go | ✔️ ([cpp](generated/golang/internal/syscall/windows/registry/syscall.cpp), [h](generated/golang/internal/syscall/windows/registry/syscall.h))| ✔️ |
| $(ImportDir)/internal/syscall/windows/registry/value.go | ✔️ ([cpp](generated/golang/internal/syscall/windows/registry/value.cpp), [h](generated/golang/internal/syscall/windows/registry/value.h))| ❌ |
| $(ImportDir)/internal/syscall/windows/registry/zsyscall_windows.go | ✔️ ([cpp](generated/golang/internal/syscall/windows/registry/zsyscall_windows.cpp), [h](generated/golang/internal/syscall/windows/registry/zsyscall_windows.h))| ❌ |
| $(ImportDir)/internal/syscall/windows/reparse_windows.go | ✔️ ([cpp](generated/golang/internal/syscall/windows/reparse_windows.cpp), [h](generated/golang/internal/syscall/windows/reparse_windows.h))| ❌ |
| $(ImportDir)/internal/syscall/windows/security_windows.go | ✔️ ([cpp](generated/golang/internal/syscall/windows/security_windows.cpp), [h](generated/golang/internal/syscall/windows/security_windows.h))| ❌ |
| $(ImportDir)/internal/syscall/windows/symlink_windows.go | ✔️ ([cpp](generated/golang/internal/syscall/windows/symlink_windows.cpp), [h](generated/golang/internal/syscall/windows/symlink_windows.h))| ✔️ |
| $(ImportDir)/internal/syscall/windows/syscall_windows.go | ✔️ ([cpp](generated/golang/internal/syscall/windows/syscall_windows.cpp), [h](generated/golang/internal/syscall/windows/syscall_windows.h))| ❌ |
| $(ImportDir)/internal/syscall/windows/sysdll/sysdll.go | ✔️ ([cpp](generated/golang/internal/syscall/windows/sysdll/sysdll.cpp), [h](generated/golang/internal/syscall/windows/sysdll/sysdll.h))| ✔️ |
| $(ImportDir)/internal/syscall/windows/zsyscall_windows.go | ✔️ ([cpp](generated/golang/internal/syscall/windows/zsyscall_windows.cpp), [h](generated/golang/internal/syscall/windows/zsyscall_windows.h))| ❌ |
| $(ImportDir)/internal/testlog/log.go | ✔️ ([cpp](generated/golang/internal/testlog/log.cpp), [h](generated/golang/internal/testlog/log.h))| ❌ |
| $(ImportDir)/internal/unsafeheader/unsafeheader.go | ✔️ ([cpp](generated/golang/internal/unsafeheader/unsafeheader.cpp), [h](generated/golang/internal/unsafeheader/unsafeheader.h))| ✔️ |
| $(ImportDir)/io/fs/format.go | ✔️ ([cpp](generated/golang/io/fs/format.cpp), [h](generated/golang/io/fs/format.h))| ❌ |
| $(ImportDir)/io/fs/fs.go | ✔️ ([cpp](generated/golang/io/fs/fs.cpp), [h](generated/golang/io/fs/fs.h))| ❌ |
| $(ImportDir)/io/io.go | ✔️ ([cpp](generated/golang/io/io.cpp), [h](generated/golang/io/io.h))| ❌ |
| $(ImportDir)/math/abs.go | ✔️ ([cpp](generated/golang/math/abs.cpp), [h](generated/golang/math/abs.h))| ❌ |
| $(ImportDir)/math/bits.go | ✔️ ([cpp](generated/golang/math/bits.cpp), [h](generated/golang/math/bits.h))| ✔️ |
| $(ImportDir)/math/bits/bits.go | ✔️ ([cpp](generated/golang/math/bits/bits.cpp), [h](generated/golang/math/bits/bits.h))| ❌ |
| $(ImportDir)/math/bits/bits_tables.go | ✔️ ([cpp](generated/golang/math/bits/bits_tables.cpp), [h](generated/golang/math/bits/bits_tables.h))| ❌ |
| $(ImportDir)/math/cmplx/sqrt.go | ✔️ ([cpp](generated/golang/math/cmplx/sqrt.cpp), [h](generated/golang/math/cmplx/sqrt.h))| ❌ |
| $(ImportDir)/math/const.go | ✔️ ([cpp](generated/golang/math/const.cpp), [h](generated/golang/math/const.h))| ✔️ |
| $(ImportDir)/math/copysign.go | ✔️ ([cpp](generated/golang/math/copysign.cpp), [h](generated/golang/math/copysign.h))| ❌ |
| $(ImportDir)/math/exp.go | ✔️ ([cpp](generated/golang/math/exp.cpp), [h](generated/golang/math/exp.h))| ✔️ |
| $(ImportDir)/math/exp2_noasm.go | ✔️ ([cpp](generated/golang/math/exp2_noasm.cpp), [h](generated/golang/math/exp2_noasm.h))| ✔️ |
| $(ImportDir)/math/exp_asm.go | ✔️ ([cpp](generated/golang/math/exp_asm.cpp), [h](generated/golang/math/exp_asm.h))| ✔️ |
| $(ImportDir)/math/frexp.go | ✔️ ([cpp](generated/golang/math/frexp.cpp), [h](generated/golang/math/frexp.h))| ❌ |
| $(ImportDir)/math/hypot.go | ✔️ ([cpp](generated/golang/math/hypot.cpp), [h](generated/golang/math/hypot.h))| ✔️ |
| $(ImportDir)/math/hypot_asm.go | ✔️ ([cpp](generated/golang/math/hypot_asm.cpp), [h](generated/golang/math/hypot_asm.h))| ✔️ |
| $(ImportDir)/math/ldexp.go | ✔️ ([cpp](generated/golang/math/ldexp.cpp), [h](generated/golang/math/ldexp.h))| ❌ |
| $(ImportDir)/math/log.go | ✔️ ([cpp](generated/golang/math/log.cpp), [h](generated/golang/math/log.h))| ✔️ |
| $(ImportDir)/math/log_asm.go | ✔️ ([cpp](generated/golang/math/log_asm.cpp), [h](generated/golang/math/log_asm.h))| ✔️ |
| $(ImportDir)/math/modf.go | ✔️ ([cpp](generated/golang/math/modf.cpp), [h](generated/golang/math/modf.h))| ❌ |
| $(ImportDir)/math/modf_noasm.go | ✔️ ([cpp](generated/golang/math/modf_noasm.cpp), [h](generated/golang/math/modf_noasm.h))| ❌ |
| $(ImportDir)/math/pow.go | ✔️ ([cpp](generated/golang/math/pow.cpp), [h](generated/golang/math/pow.h))| ✔️ |
| $(ImportDir)/math/rand/exp.go | ✔️ ([cpp](generated/golang/math/rand/exp.cpp), [h](generated/golang/math/rand/exp.h))| ✔️ |
| $(ImportDir)/math/rand/normal.go | ✔️ ([cpp](generated/golang/math/rand/normal.cpp), [h](generated/golang/math/rand/normal.h))| ✔️ |
| $(ImportDir)/math/rand/rand.go | ✔️ ([cpp](generated/golang/math/rand/rand.cpp), [h](generated/golang/math/rand/rand.h))| ❌ |
| $(ImportDir)/math/rand/rng.go | ✔️ ([cpp](generated/golang/math/rand/rng.cpp), [h](generated/golang/math/rand/rng.h))| ✔️ |
| $(ImportDir)/math/signbit.go | ✔️ ([cpp](generated/golang/math/signbit.cpp), [h](generated/golang/math/signbit.h))| ✔️ |
| $(ImportDir)/math/sqrt.go | ✔️ ([cpp](generated/golang/math/sqrt.cpp), [h](generated/golang/math/sqrt.h))| ❌ |
| $(ImportDir)/math/stubs.go | ✔️ ([cpp](generated/golang/math/stubs.cpp), [h](generated/golang/math/stubs.h))| ✔️ |
| $(ImportDir)/math/unsafe.go | ✔️ ([cpp](generated/golang/math/unsafe.cpp), [h](generated/golang/math/unsafe.h))| ✔️ |
| $(ImportDir)/os/dir.go | ✔️ ([cpp](generated/golang/os/dir.cpp), [h](generated/golang/os/dir.h))| ❌ |
| $(ImportDir)/os/dir_windows.go | ✔️ ([cpp](generated/golang/os/dir_windows.cpp), [h](generated/golang/os/dir_windows.h))| ❌ |
| $(ImportDir)/os/env.go | ✔️ ([cpp](generated/golang/os/env.cpp), [h](generated/golang/os/env.h))| ❌ |
| $(ImportDir)/os/error.go | ✔️ ([cpp](generated/golang/os/error.cpp), [h](generated/golang/os/error.h))| ❌ |
| $(ImportDir)/os/error_errno.go | ✔️ ([cpp](generated/golang/os/error_errno.cpp), [h](generated/golang/os/error_errno.h))| ✔️ |
| $(ImportDir)/os/file.go | ✔️ ([cpp](generated/golang/os/file.cpp), [h](generated/golang/os/file.h))| ❌ |
| $(ImportDir)/os/file_posix.go | ✔️ ([cpp](generated/golang/os/file_posix.cpp), [h](generated/golang/os/file_posix.h))| ❌ |
| $(ImportDir)/os/file_windows.go | ✔️ ([cpp](generated/golang/os/file_windows.cpp), [h](generated/golang/os/file_windows.h))| ❌ |
| $(ImportDir)/os/getwd.go | ✔️ ([cpp](generated/golang/os/getwd.cpp), [h](generated/golang/os/getwd.h))| ❌ |
| $(ImportDir)/os/path_windows.go | ✔️ ([cpp](generated/golang/os/path_windows.cpp), [h](generated/golang/os/path_windows.h))| ❌ |
| $(ImportDir)/os/rawconn.go | ✔️ ([cpp](generated/golang/os/rawconn.cpp), [h](generated/golang/os/rawconn.h))| ❌ |
| $(ImportDir)/os/stat.go | ✔️ ([cpp](generated/golang/os/stat.cpp), [h](generated/golang/os/stat.h))| ❌ |
| $(ImportDir)/os/stat_windows.go | ✔️ ([cpp](generated/golang/os/stat_windows.cpp), [h](generated/golang/os/stat_windows.h))| ❌ |
| $(ImportDir)/os/sticky_notbsd.go | ✔️ ([cpp](generated/golang/os/sticky_notbsd.cpp), [h](generated/golang/os/sticky_notbsd.h))| ✔️ |
| $(ImportDir)/os/types.go | ✔️ ([cpp](generated/golang/os/types.cpp), [h](generated/golang/os/types.h))| ❌ |
| $(ImportDir)/os/types_windows.go | ✔️ ([cpp](generated/golang/os/types_windows.cpp), [h](generated/golang/os/types_windows.h))| ❌ |
| $(ImportDir)/os/zero_copy_stub.go | ✔️ ([cpp](generated/golang/os/zero_copy_stub.cpp), [h](generated/golang/os/zero_copy_stub.h))| ❌ |
| $(ImportDir)/reflect/abi.go | ✔️ ([cpp](generated/golang/reflect/abi.cpp), [h](generated/golang/reflect/abi.h))| ❌ |
| $(ImportDir)/reflect/float32reg_generic.go | ✔️ ([cpp](generated/golang/reflect/float32reg_generic.cpp), [h](generated/golang/reflect/float32reg_generic.h))| ✔️ |
| $(ImportDir)/reflect/makefunc.go | ✔️ ([cpp](generated/golang/reflect/makefunc.cpp), [h](generated/golang/reflect/makefunc.h))| ❌ |
| $(ImportDir)/reflect/type.go | ✔️ ([cpp](generated/golang/reflect/type.cpp), [h](generated/golang/reflect/type.h))| ❌ |
| $(ImportDir)/reflect/value.go | ✔️ ([cpp](generated/golang/reflect/value.cpp), [h](generated/golang/reflect/value.h))| ❌ |
| $(ImportDir)/runtime/alg.go | ✔️ ([cpp](generated/golang/runtime/alg.cpp), [h](generated/golang/runtime/alg.h))| ❌ |
| $(ImportDir)/runtime/arena.go | ✔️ ([cpp](generated/golang/runtime/arena.cpp), [h](generated/golang/runtime/arena.h))| ❌ |
| $(ImportDir)/runtime/asan0.go | ✔️ ([cpp](generated/golang/runtime/asan0.cpp), [h](generated/golang/runtime/asan0.h))| ❌ |
| $(ImportDir)/runtime/atomic_pointer.go | ✔️ ([cpp](generated/golang/runtime/atomic_pointer.cpp), [h](generated/golang/runtime/atomic_pointer.h))| ❌ |
| $(ImportDir)/runtime/auxv_none.go | ✔️ ([cpp](generated/golang/runtime/auxv_none.cpp), [h](generated/golang/runtime/auxv_none.h))| ✔️ |
| $(ImportDir)/runtime/cgocall.go | ✔️ ([cpp](generated/golang/runtime/cgocall.cpp), [h](generated/golang/runtime/cgocall.h))| ❌ |
| $(ImportDir)/runtime/cgocheck.go | ✔️ ([cpp](generated/golang/runtime/cgocheck.cpp), [h](generated/golang/runtime/cgocheck.h))| ❌ |
| $(ImportDir)/runtime/chan.go | ✔️ ([cpp](generated/golang/runtime/chan.cpp), [h](generated/golang/runtime/chan.h))| ❌ |
| $(ImportDir)/runtime/coro.go | ✔️ ([cpp](generated/golang/runtime/coro.cpp), [h](generated/golang/runtime/coro.h))| ❌ |
| $(ImportDir)/runtime/cpuprof.go | ✔️ ([cpp](generated/golang/runtime/cpuprof.cpp), [h](generated/golang/runtime/cpuprof.h))| ❌ |
| $(ImportDir)/runtime/cputicks.go | ✔️ ([cpp](generated/golang/runtime/cputicks.cpp), [h](generated/golang/runtime/cputicks.h))| ✔️ |
| $(ImportDir)/runtime/debug.go | ✔️ ([cpp](generated/golang/runtime/debug.cpp), [h](generated/golang/runtime/debug.h))| ❌ |
| $(ImportDir)/runtime/debuglog.go | ✔️ ([cpp](generated/golang/runtime/debuglog.cpp), [h](generated/golang/runtime/debuglog.h))| ❌ |
| $(ImportDir)/runtime/debuglog_off.go | ✔️ ([cpp](generated/golang/runtime/debuglog_off.cpp), [h](generated/golang/runtime/debuglog_off.h))| ✔️ |
| $(ImportDir)/runtime/defs_windows.go | ✔️ ([cpp](generated/golang/runtime/defs_windows.cpp), [h](generated/golang/runtime/defs_windows.h))| ✔️ |
| $(ImportDir)/runtime/defs_windows_amd64.go | ✔️ ([cpp](generated/golang/runtime/defs_windows_amd64.cpp), [h](generated/golang/runtime/defs_windows_amd64.h))| ❌ |
| $(ImportDir)/runtime/env_posix.go | ✔️ ([cpp](generated/golang/runtime/env_posix.cpp), [h](generated/golang/runtime/env_posix.h))| ❌ |
| $(ImportDir)/runtime/error.go | ✔️ ([cpp](generated/golang/runtime/error.cpp), [h](generated/golang/runtime/error.h))| ❌ |
| $(ImportDir)/runtime/exithook.go | ✔️ ([cpp](generated/golang/runtime/exithook.cpp), [h](generated/golang/runtime/exithook.h))| ❌ |
| $(ImportDir)/runtime/extern.go | ✔️ ([cpp](generated/golang/runtime/extern.cpp), [h](generated/golang/runtime/extern.h))| ❌ |
| $(ImportDir)/runtime/fastlog2.go | ✔️ ([cpp](generated/golang/runtime/fastlog2.cpp), [h](generated/golang/runtime/fastlog2.h))| ✔️ |
| $(ImportDir)/runtime/fastlog2table.go | ✔️ ([cpp](generated/golang/runtime/fastlog2table.cpp), [h](generated/golang/runtime/fastlog2table.h))| ✔️ |
| $(ImportDir)/runtime/fds_nonunix.go | ✔️ ([cpp](generated/golang/runtime/fds_nonunix.cpp), [h](generated/golang/runtime/fds_nonunix.h))| ✔️ |
| $(ImportDir)/runtime/float.go | ✔️ ([cpp](generated/golang/runtime/float.cpp), [h](generated/golang/runtime/float.h))| ❌ |
| $(ImportDir)/runtime/hash64.go | ✔️ ([cpp](generated/golang/runtime/hash64.cpp), [h](generated/golang/runtime/hash64.h))| ❌ |
| $(ImportDir)/runtime/histogram.go | ✔️ ([cpp](generated/golang/runtime/histogram.cpp), [h](generated/golang/runtime/histogram.h))| ❌ |
| $(ImportDir)/runtime/iface.go | ✔️ ([cpp](generated/golang/runtime/iface.cpp), [h](generated/golang/runtime/iface.h))| ❌ |
| $(ImportDir)/runtime/internal/atomic/atomic_amd64.go | ✔️ ([cpp](generated/golang/runtime/internal/atomic/atomic_amd64.cpp), [h](generated/golang/runtime/internal/atomic/atomic_amd64.h))| ❌ |
| $(ImportDir)/runtime/internal/atomic/stubs.go | ✔️ ([cpp](generated/golang/runtime/internal/atomic/stubs.cpp), [h](generated/golang/runtime/internal/atomic/stubs.h))| ❌ |
| $(ImportDir)/runtime/internal/atomic/types.go | ✔️ ([cpp](generated/golang/runtime/internal/atomic/types.cpp), [h](generated/golang/runtime/internal/atomic/types.h))| ❌ |
| $(ImportDir)/runtime/internal/math/math.go | ✔️ ([cpp](generated/golang/runtime/internal/math/math.cpp), [h](generated/golang/runtime/internal/math/math.h))| ❌ |
| $(ImportDir)/runtime/internal/sys/consts.go | ✔️ ([cpp](generated/golang/runtime/internal/sys/consts.cpp), [h](generated/golang/runtime/internal/sys/consts.h))| ✔️ |
| $(ImportDir)/runtime/internal/sys/consts_norace.go | ✔️ ([cpp](generated/golang/runtime/internal/sys/consts_norace.cpp), [h](generated/golang/runtime/internal/sys/consts_norace.h))| ✔️ |
| $(ImportDir)/runtime/internal/sys/intrinsics.go | ✔️ ([cpp](generated/golang/runtime/internal/sys/intrinsics.cpp), [h](generated/golang/runtime/internal/sys/intrinsics.h))| ❌ |
| $(ImportDir)/runtime/internal/sys/nih.go | ✔️ ([cpp](generated/golang/runtime/internal/sys/nih.cpp), [h](generated/golang/runtime/internal/sys/nih.h))| ✔️ |
| $(ImportDir)/runtime/lfstack.go | ✔️ ([cpp](generated/golang/runtime/lfstack.cpp), [h](generated/golang/runtime/lfstack.h))| ❌ |
| $(ImportDir)/runtime/lock_sema.go | ✔️ ([cpp](generated/golang/runtime/lock_sema.cpp), [h](generated/golang/runtime/lock_sema.h))| ❌ |
| $(ImportDir)/runtime/lockrank.go | ✔️ ([cpp](generated/golang/runtime/lockrank.cpp), [h](generated/golang/runtime/lockrank.h))| ❌ |
| $(ImportDir)/runtime/lockrank_off.go | ✔️ ([cpp](generated/golang/runtime/lockrank_off.cpp), [h](generated/golang/runtime/lockrank_off.h))| ❌ |
| $(ImportDir)/runtime/malloc.go | ✔️ ([cpp](generated/golang/runtime/malloc.cpp), [h](generated/golang/runtime/malloc.h))| ❌ |
| $(ImportDir)/runtime/map.go | ✔️ ([cpp](generated/golang/runtime/map.cpp), [h](generated/golang/runtime/map.h))| ❌ |
| $(ImportDir)/runtime/map_faststr.go | ✔️ ([cpp](generated/golang/runtime/map_faststr.cpp), [h](generated/golang/runtime/map_faststr.h))| ❌ |
| $(ImportDir)/runtime/mbarrier.go | ✔️ ([cpp](generated/golang/runtime/mbarrier.cpp), [h](generated/golang/runtime/mbarrier.h))| ❌ |
| $(ImportDir)/runtime/mbitmap.go | ✔️ ([cpp](generated/golang/runtime/mbitmap.cpp), [h](generated/golang/runtime/mbitmap.h))| ❌ |
| $(ImportDir)/runtime/mbitmap_allocheaders.go | ✔️ ([cpp](generated/golang/runtime/mbitmap_allocheaders.cpp), [h](generated/golang/runtime/mbitmap_allocheaders.h))| ❌ |
| $(ImportDir)/runtime/mcache.go | ✔️ ([cpp](generated/golang/runtime/mcache.cpp), [h](generated/golang/runtime/mcache.h))| ❌ |
| $(ImportDir)/runtime/mcentral.go | ✔️ ([cpp](generated/golang/runtime/mcentral.cpp), [h](generated/golang/runtime/mcentral.h))| ❌ |
| $(ImportDir)/runtime/mcheckmark.go | ✔️ ([cpp](generated/golang/runtime/mcheckmark.cpp), [h](generated/golang/runtime/mcheckmark.h))| ❌ |
| $(ImportDir)/runtime/mem.go | ✔️ ([cpp](generated/golang/runtime/mem.cpp), [h](generated/golang/runtime/mem.h))| ❌ |
| $(ImportDir)/runtime/mem_windows.go | ✔️ ([cpp](generated/golang/runtime/mem_windows.cpp), [h](generated/golang/runtime/mem_windows.h))| ❌ |
| $(ImportDir)/runtime/metrics.go | ✔️ ([cpp](generated/golang/runtime/metrics.cpp), [h](generated/golang/runtime/metrics.h))| ❌ |
| $(ImportDir)/runtime/mfinal.go | ✔️ ([cpp](generated/golang/runtime/mfinal.cpp), [h](generated/golang/runtime/mfinal.h))| ❌ |
| $(ImportDir)/runtime/mfixalloc.go | ✔️ ([cpp](generated/golang/runtime/mfixalloc.cpp), [h](generated/golang/runtime/mfixalloc.h))| ❌ |
| $(ImportDir)/runtime/mgc.go | ✔️ ([cpp](generated/golang/runtime/mgc.cpp), [h](generated/golang/runtime/mgc.h))| ❌ |
| $(ImportDir)/runtime/mgclimit.go | ✔️ ([cpp](generated/golang/runtime/mgclimit.cpp), [h](generated/golang/runtime/mgclimit.h))| ❌ |
| $(ImportDir)/runtime/mgcmark.go | ✔️ ([cpp](generated/golang/runtime/mgcmark.cpp), [h](generated/golang/runtime/mgcmark.h))| ❌ |
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
| $(ImportDir)/runtime/msize_allocheaders.go | ✔️ ([cpp](generated/golang/runtime/msize_allocheaders.cpp), [h](generated/golang/runtime/msize_allocheaders.h))| ❌ |
| $(ImportDir)/runtime/mspanset.go | ✔️ ([cpp](generated/golang/runtime/mspanset.cpp), [h](generated/golang/runtime/mspanset.h))| ❌ |
| $(ImportDir)/runtime/mstats.go | ✔️ ([cpp](generated/golang/runtime/mstats.cpp), [h](generated/golang/runtime/mstats.h))| ❌ |
| $(ImportDir)/runtime/mwbbuf.go | ✔️ ([cpp](generated/golang/runtime/mwbbuf.cpp), [h](generated/golang/runtime/mwbbuf.h))| ❌ |
| $(ImportDir)/runtime/netpoll.go | ✔️ ([cpp](generated/golang/runtime/netpoll.cpp), [h](generated/golang/runtime/netpoll.h))| ❌ |
| $(ImportDir)/runtime/netpoll_windows.go | ✔️ ([cpp](generated/golang/runtime/netpoll_windows.cpp), [h](generated/golang/runtime/netpoll_windows.h))| ❌ |
| $(ImportDir)/runtime/os_nonopenbsd.go | ✔️ ([cpp](generated/golang/runtime/os_nonopenbsd.cpp), [h](generated/golang/runtime/os_nonopenbsd.h))| ❌ |
| $(ImportDir)/runtime/os_windows.go | ✔️ ([cpp](generated/golang/runtime/os_windows.cpp), [h](generated/golang/runtime/os_windows.h))| ❌ |
| $(ImportDir)/runtime/pagetrace_off.go | ✔️ ([cpp](generated/golang/runtime/pagetrace_off.cpp), [h](generated/golang/runtime/pagetrace_off.h))| ❌ |
| $(ImportDir)/runtime/panic.go | ✔️ ([cpp](generated/golang/runtime/panic.cpp), [h](generated/golang/runtime/panic.h))| ❌ |
| $(ImportDir)/runtime/pinner.go | ✔️ ([cpp](generated/golang/runtime/pinner.cpp), [h](generated/golang/runtime/pinner.h))| ❌ |
| $(ImportDir)/runtime/plugin.go | ✔️ ([cpp](generated/golang/runtime/plugin.cpp), [h](generated/golang/runtime/plugin.h))| ❌ |
| $(ImportDir)/runtime/preempt.go | ✔️ ([cpp](generated/golang/runtime/preempt.cpp), [h](generated/golang/runtime/preempt.h))| ❌ |
| $(ImportDir)/runtime/print.go | ✔️ ([cpp](generated/golang/runtime/print.cpp), [h](generated/golang/runtime/print.h))| ❌ |
| $(ImportDir)/runtime/proc.go | ✔️ ([cpp](generated/golang/runtime/proc.cpp), [h](generated/golang/runtime/proc.h))| ❌ |
| $(ImportDir)/runtime/profbuf.go | ✔️ ([cpp](generated/golang/runtime/profbuf.cpp), [h](generated/golang/runtime/profbuf.h))| ❌ |
| $(ImportDir)/runtime/race0.go | ✔️ ([cpp](generated/golang/runtime/race0.cpp), [h](generated/golang/runtime/race0.h))| ❌ |
| $(ImportDir)/runtime/rand.go | ✔️ ([cpp](generated/golang/runtime/rand.cpp), [h](generated/golang/runtime/rand.h))| ❌ |
| $(ImportDir)/runtime/runtime.go | ✔️ ([cpp](generated/golang/runtime/runtime.cpp), [h](generated/golang/runtime/runtime.h))| ❌ |
| $(ImportDir)/runtime/runtime1.go | ✔️ ([cpp](generated/golang/runtime/runtime1.cpp), [h](generated/golang/runtime/runtime1.h))| ❌ |
| $(ImportDir)/runtime/runtime2.go | ✔️ ([cpp](generated/golang/runtime/runtime2.cpp), [h](generated/golang/runtime/runtime2.h))| ❌ |
| $(ImportDir)/runtime/rwmutex.go | ✔️ ([cpp](generated/golang/runtime/rwmutex.cpp), [h](generated/golang/runtime/rwmutex.h))| ❌ |
| $(ImportDir)/runtime/security_nonunix.go | ✔️ ([cpp](generated/golang/runtime/security_nonunix.cpp), [h](generated/golang/runtime/security_nonunix.h))| ✔️ |
| $(ImportDir)/runtime/select.go | ✔️ ([cpp](generated/golang/runtime/select.cpp), [h](generated/golang/runtime/select.h))| ❌ |
| $(ImportDir)/runtime/sema.go | ✔️ ([cpp](generated/golang/runtime/sema.cpp), [h](generated/golang/runtime/sema.h))| ❌ |
| $(ImportDir)/runtime/signal_windows.go | ✔️ ([cpp](generated/golang/runtime/signal_windows.cpp), [h](generated/golang/runtime/signal_windows.h))| ❌ |
| $(ImportDir)/runtime/sigqueue.go | ✔️ ([cpp](generated/golang/runtime/sigqueue.cpp), [h](generated/golang/runtime/sigqueue.h))| ❌ |
| $(ImportDir)/runtime/sigqueue_note.go | ✔️ ([cpp](generated/golang/runtime/sigqueue_note.cpp), [h](generated/golang/runtime/sigqueue_note.h))| ❌ |
| $(ImportDir)/runtime/sizeclasses.go | ✔️ ([cpp](generated/golang/runtime/sizeclasses.cpp), [h](generated/golang/runtime/sizeclasses.h))| ✔️ |
| $(ImportDir)/runtime/slice.go | ✔️ ([cpp](generated/golang/runtime/slice.cpp), [h](generated/golang/runtime/slice.h))| ❌ |
| $(ImportDir)/runtime/stack.go | ✔️ ([cpp](generated/golang/runtime/stack.cpp), [h](generated/golang/runtime/stack.h))| ❌ |
| $(ImportDir)/runtime/stkframe.go | ✔️ ([cpp](generated/golang/runtime/stkframe.cpp), [h](generated/golang/runtime/stkframe.h))| ❌ |
| $(ImportDir)/runtime/string.go | ✔️ ([cpp](generated/golang/runtime/string.cpp), [h](generated/golang/runtime/string.h))| ❌ |
| $(ImportDir)/runtime/stubs.go | ✔️ ([cpp](generated/golang/runtime/stubs.cpp), [h](generated/golang/runtime/stubs.h))| ❌ |
| $(ImportDir)/runtime/stubs3.go | ✔️ ([cpp](generated/golang/runtime/stubs3.cpp), [h](generated/golang/runtime/stubs3.h))| ✔️ |
| $(ImportDir)/runtime/stubs_amd64.go | ✔️ ([cpp](generated/golang/runtime/stubs_amd64.cpp), [h](generated/golang/runtime/stubs_amd64.h))| ❌ |
| $(ImportDir)/runtime/stubs_nonlinux.go | ✔️ ([cpp](generated/golang/runtime/stubs_nonlinux.cpp), [h](generated/golang/runtime/stubs_nonlinux.h))| ✔️ |
| $(ImportDir)/runtime/symtab.go | ✔️ ([cpp](generated/golang/runtime/symtab.cpp), [h](generated/golang/runtime/symtab.h))| ❌ |
| $(ImportDir)/runtime/symtabinl.go | ✔️ ([cpp](generated/golang/runtime/symtabinl.cpp), [h](generated/golang/runtime/symtabinl.h))| ❌ |
| $(ImportDir)/runtime/sys_nonppc64x.go | ✔️ ([cpp](generated/golang/runtime/sys_nonppc64x.cpp), [h](generated/golang/runtime/sys_nonppc64x.h))| ✔️ |
| $(ImportDir)/runtime/sys_x86.go | ✔️ ([cpp](generated/golang/runtime/sys_x86.cpp), [h](generated/golang/runtime/sys_x86.h))| ❌ |
| $(ImportDir)/runtime/syscall_windows.go | ✔️ ([cpp](generated/golang/runtime/syscall_windows.cpp), [h](generated/golang/runtime/syscall_windows.h))| ❌ |
| $(ImportDir)/runtime/tagptr.go | ✔️ ([cpp](generated/golang/runtime/tagptr.cpp), [h](generated/golang/runtime/tagptr.h))| ✔️ |
| $(ImportDir)/runtime/tagptr_64bit.go | ✔️ ([cpp](generated/golang/runtime/tagptr_64bit.cpp), [h](generated/golang/runtime/tagptr_64bit.h))| ❌ |
| $(ImportDir)/runtime/time.go | ✔️ ([cpp](generated/golang/runtime/time.cpp), [h](generated/golang/runtime/time.h))| ❌ |
| $(ImportDir)/runtime/time_nofake.go | ✔️ ([cpp](generated/golang/runtime/time_nofake.cpp), [h](generated/golang/runtime/time_nofake.h))| ❌ |
| $(ImportDir)/runtime/timeasm.go | ✔️ ([cpp](generated/golang/runtime/timeasm.cpp), [h](generated/golang/runtime/timeasm.h))| ✔️ |
| $(ImportDir)/runtime/tls_windows_amd64.go | ✔️ ([cpp](generated/golang/runtime/tls_windows_amd64.cpp), [h](generated/golang/runtime/tls_windows_amd64.h))| ❌ |
| $(ImportDir)/runtime/trace2.go | ✔️ ([cpp](generated/golang/runtime/trace2.cpp), [h](generated/golang/runtime/trace2.h))| ❌ |
| $(ImportDir)/runtime/trace2buf.go | ✔️ ([cpp](generated/golang/runtime/trace2buf.cpp), [h](generated/golang/runtime/trace2buf.h))| ❌ |
| $(ImportDir)/runtime/trace2cpu.go | ✔️ ([cpp](generated/golang/runtime/trace2cpu.cpp), [h](generated/golang/runtime/trace2cpu.h))| ❌ |
| $(ImportDir)/runtime/trace2event.go | ✔️ ([cpp](generated/golang/runtime/trace2event.cpp), [h](generated/golang/runtime/trace2event.h))| ❌ |
| $(ImportDir)/runtime/trace2map.go | ✔️ ([cpp](generated/golang/runtime/trace2map.cpp), [h](generated/golang/runtime/trace2map.h))| ❌ |
| $(ImportDir)/runtime/trace2region.go | ✔️ ([cpp](generated/golang/runtime/trace2region.cpp), [h](generated/golang/runtime/trace2region.h))| ❌ |
| $(ImportDir)/runtime/trace2runtime.go | ✔️ ([cpp](generated/golang/runtime/trace2runtime.cpp), [h](generated/golang/runtime/trace2runtime.h))| ❌ |
| $(ImportDir)/runtime/trace2stack.go | ✔️ ([cpp](generated/golang/runtime/trace2stack.cpp), [h](generated/golang/runtime/trace2stack.h))| ❌ |
| $(ImportDir)/runtime/trace2status.go | ✔️ ([cpp](generated/golang/runtime/trace2status.cpp), [h](generated/golang/runtime/trace2status.h))| ❌ |
| $(ImportDir)/runtime/trace2string.go | ✔️ ([cpp](generated/golang/runtime/trace2string.cpp), [h](generated/golang/runtime/trace2string.h))| ❌ |
| $(ImportDir)/runtime/trace2time.go | ✔️ ([cpp](generated/golang/runtime/trace2time.cpp), [h](generated/golang/runtime/trace2time.h))| ❌ |
| $(ImportDir)/runtime/traceback.go | ✔️ ([cpp](generated/golang/runtime/traceback.cpp), [h](generated/golang/runtime/traceback.h))| ❌ |
| $(ImportDir)/runtime/type.go | ✔️ ([cpp](generated/golang/runtime/type.cpp), [h](generated/golang/runtime/type.h))| ❌ |
| $(ImportDir)/runtime/typekind.go | ✔️ ([cpp](generated/golang/runtime/typekind.cpp), [h](generated/golang/runtime/typekind.h))| ❌ |
| $(ImportDir)/runtime/utf8.go | ✔️ ([cpp](generated/golang/runtime/utf8.cpp), [h](generated/golang/runtime/utf8.h))| ❌ |
| $(ImportDir)/runtime/vdso_in_none.go | ✔️ ([cpp](generated/golang/runtime/vdso_in_none.cpp), [h](generated/golang/runtime/vdso_in_none.h))| ✔️ |
| $(ImportDir)/runtime/write_err.go | ✔️ ([cpp](generated/golang/runtime/write_err.cpp), [h](generated/golang/runtime/write_err.h))| ❌ |
| $(ImportDir)/runtime/zcallback_windows.go | ✔️ ([cpp](generated/golang/runtime/zcallback_windows.cpp), [h](generated/golang/runtime/zcallback_windows.h))| ✔️ |
| $(ImportDir)/slices/slices.go | ✔️ ([cpp](generated/golang/slices/slices.cpp), [h](generated/golang/slices/slices.h))| ❌ |
| $(ImportDir)/slices/sort.go | ✔️ ([cpp](generated/golang/slices/sort.cpp), [h](generated/golang/slices/sort.h))| ✔️ |
| $(ImportDir)/slices/zsortanyfunc.go | ✔️ ([cpp](generated/golang/slices/zsortanyfunc.cpp), [h](generated/golang/slices/zsortanyfunc.h))| ✔️ |
| $(ImportDir)/slices/zsortordered.go | ✔️ ([cpp](generated/golang/slices/zsortordered.cpp), [h](generated/golang/slices/zsortordered.h))| ✔️ |
| $(ImportDir)/sort/slice.go | ✔️ ([cpp](generated/golang/sort/slice.cpp), [h](generated/golang/sort/slice.h))| ✔️ |
| $(ImportDir)/sort/sort.go | ✔️ ([cpp](generated/golang/sort/sort.cpp), [h](generated/golang/sort/sort.h))| ❌ |
| $(ImportDir)/sort/sort_impl_go121.go | ✔️ ([cpp](generated/golang/sort/sort_impl_go121.cpp), [h](generated/golang/sort/sort_impl_go121.h))| ❌ |
| $(ImportDir)/sort/zsortfunc.go | ✔️ ([cpp](generated/golang/sort/zsortfunc.cpp), [h](generated/golang/sort/zsortfunc.h))| ❌ |
| $(ImportDir)/sort/zsortinterface.go | ✔️ ([cpp](generated/golang/sort/zsortinterface.cpp), [h](generated/golang/sort/zsortinterface.h))| ✔️ |
| $(ImportDir)/strconv/atoi.go | ✔️ ([cpp](generated/golang/strconv/atoi.cpp), [h](generated/golang/strconv/atoi.h))| ❌ |
| $(ImportDir)/strconv/bytealg.go | ✔️ ([cpp](generated/golang/strconv/bytealg.cpp), [h](generated/golang/strconv/bytealg.h))| ✔️ |
| $(ImportDir)/strconv/decimal.go | ✔️ ([cpp](generated/golang/strconv/decimal.cpp), [h](generated/golang/strconv/decimal.h))| ❌ |
| $(ImportDir)/strconv/eisel_lemire.go | ✔️ ([cpp](generated/golang/strconv/eisel_lemire.cpp), [h](generated/golang/strconv/eisel_lemire.h))| ✔️ |
| $(ImportDir)/strconv/ftoa.go | ✔️ ([cpp](generated/golang/strconv/ftoa.cpp), [h](generated/golang/strconv/ftoa.h))| ❌ |
| $(ImportDir)/strconv/ftoaryu.go | ✔️ ([cpp](generated/golang/strconv/ftoaryu.cpp), [h](generated/golang/strconv/ftoaryu.h))| ❌ |
| $(ImportDir)/strconv/itoa.go | ✔️ ([cpp](generated/golang/strconv/itoa.cpp), [h](generated/golang/strconv/itoa.h))| ❌ |
| $(ImportDir)/strconv/quote.go | ✔️ ([cpp](generated/golang/strconv/quote.cpp), [h](generated/golang/strconv/quote.h))| ❌ |
| $(ImportDir)/strings/builder.go | ✔️ ([cpp](generated/golang/strings/builder.cpp), [h](generated/golang/strings/builder.h))| ❌ |
| $(ImportDir)/strings/reader.go | ✔️ ([cpp](generated/golang/strings/reader.cpp), [h](generated/golang/strings/reader.h))| ❌ |
| $(ImportDir)/strings/strings.go | ✔️ ([cpp](generated/golang/strings/strings.cpp), [h](generated/golang/strings/strings.h))| ❌ |
| $(ImportDir)/sync/atomic/doc.go | ✔️ ([cpp](generated/golang/sync/atomic/doc.cpp), [h](generated/golang/sync/atomic/doc.h))| ❌ |
| $(ImportDir)/sync/atomic/type.go | ✔️ ([cpp](generated/golang/sync/atomic/type.cpp), [h](generated/golang/sync/atomic/type.h))| ✔️ |
| $(ImportDir)/sync/atomic/value.go | ✔️ ([cpp](generated/golang/sync/atomic/value.cpp), [h](generated/golang/sync/atomic/value.h))| ❌ |
| $(ImportDir)/sync/cond.go | ✔️ ([cpp](generated/golang/sync/cond.cpp), [h](generated/golang/sync/cond.h))| ❌ |
| $(ImportDir)/sync/map.go | ✔️ ([cpp](generated/golang/sync/map.cpp), [h](generated/golang/sync/map.h))| ❌ |
| $(ImportDir)/sync/mutex.go | ✔️ ([cpp](generated/golang/sync/mutex.cpp), [h](generated/golang/sync/mutex.h))| ❌ |
| $(ImportDir)/sync/once.go | ✔️ ([cpp](generated/golang/sync/once.cpp), [h](generated/golang/sync/once.h))| ✔️ |
| $(ImportDir)/sync/oncefunc.go | ✔️ ([cpp](generated/golang/sync/oncefunc.cpp), [h](generated/golang/sync/oncefunc.h))| ❌ |
| $(ImportDir)/sync/pool.go | ✔️ ([cpp](generated/golang/sync/pool.cpp), [h](generated/golang/sync/pool.h))| ❌ |
| $(ImportDir)/sync/poolqueue.go | ✔️ ([cpp](generated/golang/sync/poolqueue.cpp), [h](generated/golang/sync/poolqueue.h))| ❌ |
| $(ImportDir)/sync/runtime.go | ✔️ ([cpp](generated/golang/sync/runtime.cpp), [h](generated/golang/sync/runtime.h))| ✔️ |
| $(ImportDir)/sync/runtime2.go | ✔️ ([cpp](generated/golang/sync/runtime2.cpp), [h](generated/golang/sync/runtime2.h))| ✔️ |
| $(ImportDir)/sync/rwmutex.go | ✔️ ([cpp](generated/golang/sync/rwmutex.cpp), [h](generated/golang/sync/rwmutex.h))| ❌ |
| $(ImportDir)/syscall/asan0.go | ✔️ ([cpp](generated/golang/syscall/asan0.cpp), [h](generated/golang/syscall/asan0.h))| ❌ |
| $(ImportDir)/syscall/dll_windows.go | ✔️ ([cpp](generated/golang/syscall/dll_windows.cpp), [h](generated/golang/syscall/dll_windows.h))| ❌ |
| $(ImportDir)/syscall/env_windows.go | ✔️ ([cpp](generated/golang/syscall/env_windows.cpp), [h](generated/golang/syscall/env_windows.h))| ❌ |
| $(ImportDir)/syscall/exec_windows.go | ✔️ ([cpp](generated/golang/syscall/exec_windows.cpp), [h](generated/golang/syscall/exec_windows.h))| ❌ |
| $(ImportDir)/syscall/msan0.go | ✔️ ([cpp](generated/golang/syscall/msan0.cpp), [h](generated/golang/syscall/msan0.h))| ❌ |
| $(ImportDir)/syscall/net.go | ✔️ ([cpp](generated/golang/syscall/net.cpp), [h](generated/golang/syscall/net.h))| ✔️ |
| $(ImportDir)/syscall/security_windows.go | ✔️ ([cpp](generated/golang/syscall/security_windows.cpp), [h](generated/golang/syscall/security_windows.h))| ❌ |
| $(ImportDir)/syscall/syscall.go | ✔️ ([cpp](generated/golang/syscall/syscall.cpp), [h](generated/golang/syscall/syscall.h))| ❌ |
| $(ImportDir)/syscall/syscall_windows.go | ✔️ ([cpp](generated/golang/syscall/syscall_windows.cpp), [h](generated/golang/syscall/syscall_windows.h))| ❌ |
| $(ImportDir)/syscall/types_windows.go | ✔️ ([cpp](generated/golang/syscall/types_windows.cpp), [h](generated/golang/syscall/types_windows.h))| ❌ |
| $(ImportDir)/syscall/types_windows_amd64.go | ✔️ ([cpp](generated/golang/syscall/types_windows_amd64.cpp), [h](generated/golang/syscall/types_windows_amd64.h))| ❌ |
| $(ImportDir)/syscall/wtf8_windows.go | ✔️ ([cpp](generated/golang/syscall/wtf8_windows.cpp), [h](generated/golang/syscall/wtf8_windows.h))| ❌ |
| $(ImportDir)/syscall/zerrors_windows.go | ✔️ ([cpp](generated/golang/syscall/zerrors_windows.cpp), [h](generated/golang/syscall/zerrors_windows.h))| ✔️ |
| $(ImportDir)/syscall/zsyscall_windows.go | ✔️ ([cpp](generated/golang/syscall/zsyscall_windows.cpp), [h](generated/golang/syscall/zsyscall_windows.h))| ❌ |
| $(ImportDir)/time/format.go | ✔️ ([cpp](generated/golang/time/format.cpp), [h](generated/golang/time/format.h))| ❌ |
| $(ImportDir)/time/format_rfc3339.go | ✔️ ([cpp](generated/golang/time/format_rfc3339.cpp), [h](generated/golang/time/format_rfc3339.h))| ❌ |
| $(ImportDir)/time/sleep.go | ✔️ ([cpp](generated/golang/time/sleep.cpp), [h](generated/golang/time/sleep.h))| ❌ |
| $(ImportDir)/time/sys_windows.go | ✔️ ([cpp](generated/golang/time/sys_windows.cpp), [h](generated/golang/time/sys_windows.h))| ❌ |
| $(ImportDir)/time/tick.go | ✔️ ([cpp](generated/golang/time/tick.cpp), [h](generated/golang/time/tick.h))| ❌ |
| $(ImportDir)/time/time.go | ✔️ ([cpp](generated/golang/time/time.cpp), [h](generated/golang/time/time.h))| ❌ |
| $(ImportDir)/time/zoneinfo.go | ✔️ ([cpp](generated/golang/time/zoneinfo.cpp), [h](generated/golang/time/zoneinfo.h))| ❌ |
| $(ImportDir)/time/zoneinfo_abbrs_windows.go | ✔️ ([cpp](generated/golang/time/zoneinfo_abbrs_windows.cpp), [h](generated/golang/time/zoneinfo_abbrs_windows.h))| ✔️ |
| $(ImportDir)/time/zoneinfo_goroot.go | ✔️ ([cpp](generated/golang/time/zoneinfo_goroot.cpp), [h](generated/golang/time/zoneinfo_goroot.h))| ✔️ |
| $(ImportDir)/time/zoneinfo_read.go | ✔️ ([cpp](generated/golang/time/zoneinfo_read.cpp), [h](generated/golang/time/zoneinfo_read.h))| ❌ |
| $(ImportDir)/time/zoneinfo_windows.go | ✔️ ([cpp](generated/golang/time/zoneinfo_windows.cpp), [h](generated/golang/time/zoneinfo_windows.h))| ❌ |
| $(ImportDir)/unicode/digit.go | ✔️ ([cpp](generated/golang/unicode/digit.cpp), [h](generated/golang/unicode/digit.h))| ❌ |
| $(ImportDir)/unicode/graphic.go | ✔️ ([cpp](generated/golang/unicode/graphic.cpp), [h](generated/golang/unicode/graphic.h))| ❌ |
| $(ImportDir)/unicode/letter.go | ✔️ ([cpp](generated/golang/unicode/letter.cpp), [h](generated/golang/unicode/letter.h))| ❌ |
| $(ImportDir)/unicode/tables.go | ✔️ ([cpp](generated/golang/unicode/tables.cpp), [h](generated/golang/unicode/tables.h))| ❌ |
| $(ImportDir)/unicode/utf16/utf16.go | ✔️ ([cpp](generated/golang/unicode/utf16/utf16.cpp), [h](generated/golang/unicode/utf16/utf16.h))| ❌ |
| $(ImportDir)/unicode/utf8/utf8.go | ✔️ ([cpp](generated/golang/unicode/utf8/utf8.cpp), [h](generated/golang/unicode/utf8/utf8.h))| ❌ |
| $(ImportDir)/unsafe/unsafe.go | ✔️ ([cpp](generated/golang/unsafe/unsafe.cpp), [h](generated/golang/unsafe/unsafe.h))| ✔️ |
