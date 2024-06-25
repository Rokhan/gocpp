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
| [TourOfGo/basics/named-results.go](tests/TourOfGo/basics/named-results.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/basics/named-results.cpp)) | ❌ |
| [TourOfGo/basics/numeric-constants.go](tests/TourOfGo/basics/numeric-constants.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/basics/numeric-constants.cpp)) | ❌ |
| [TourOfGo/basics/packages.go](tests/TourOfGo/basics/packages.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/basics/packages.cpp)) | ➖ | 
| [TourOfGo/basics/panic-recover.go](tests/TourOfGo/basics/panic-recover.go) | ✔️ | ❌ | ❌ | ❌ |
| [TourOfGo/basics/short-variable-declarations.go](tests/TourOfGo/basics/short-variable-declarations.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/basics/short-variable-declarations.cpp)) | ✔️ |
| [TourOfGo/basics/type-conversions.go](tests/TourOfGo/basics/type-conversions.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/basics/type-conversions.cpp)) | ✔️ |
| [TourOfGo/basics/type-inference.go](tests/TourOfGo/basics/type-inference.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/basics/type-inference.cpp)) | ❌ |
| [TourOfGo/basics/variables.go](tests/TourOfGo/basics/variables.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/basics/variables.cpp)) | ✔️ |
| [TourOfGo/basics/variables-mixed-declaration.go](tests/TourOfGo/basics/variables-mixed-declaration.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/basics/variables-mixed-declaration.cpp)) | ✔️ |
| [TourOfGo/basics/variables-with-initializers.go](tests/TourOfGo/basics/variables-with-initializers.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/basics/variables-with-initializers.cpp)) | ✔️ |
| [TourOfGo/basics/zero.go](tests/TourOfGo/basics/zero.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/basics/zero.cpp)) | ❌ |
| [TourOfGo/concurrency/buffered-channels.go](tests/TourOfGo/concurrency/buffered-channels.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/concurrency/buffered-channels.cpp)) | ✔️ |
| [TourOfGo/concurrency/channels.go](tests/TourOfGo/concurrency/channels.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/concurrency/channels.cpp)) | ❌ |
| [TourOfGo/concurrency/channels-opt.go](tests/TourOfGo/concurrency/channels-opt.go) | ✔️ | ❌ | ❌ | ❌ |
| [TourOfGo/concurrency/default-selection.go](tests/TourOfGo/concurrency/default-selection.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/concurrency/default-selection.cpp)) | ❌ |
| [TourOfGo/concurrency/exercise-equivalent-binary-trees.go](tests/TourOfGo/concurrency/exercise-equivalent-binary-trees.go) | ✔️ | ❌ | ❌ | ❌ |
| [TourOfGo/concurrency/exercise-web-crawler.go](tests/TourOfGo/concurrency/exercise-web-crawler.go) | ✔️ | ❌ | ❌ | ❌ |
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
| [TourOfGo/flowcontrol/switch.go](tests/TourOfGo/flowcontrol/switch.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/flowcontrol/switch.cpp)) | ❌ |
| [TourOfGo/flowcontrol/switch-evaluation-order.go](tests/TourOfGo/flowcontrol/switch-evaluation-order.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/flowcontrol/switch-evaluation-order.cpp)) | ➖ | 
| [TourOfGo/flowcontrol/switch-numeric.go](tests/TourOfGo/flowcontrol/switch-numeric.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/flowcontrol/switch-numeric.cpp)) | ➖ | 
| [TourOfGo/flowcontrol/switch-with-no-condition.go](tests/TourOfGo/flowcontrol/switch-with-no-condition.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/flowcontrol/switch-with-no-condition.cpp)) | ➖ | 
| [TourOfGo/generics/generics.go](tests/TourOfGo/generics/generics.go) | ✔️ | ❌ | ❌ | ❌ |
| [TourOfGo/methods/empty-interface.go](tests/TourOfGo/methods/empty-interface.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/methods/empty-interface.cpp)) | ❌ |
| [TourOfGo/methods/errors.go](tests/TourOfGo/methods/errors.go) | ✔️ | ❌ | ❌ | ❌ |
| [TourOfGo/methods/exercise-errors.go](tests/TourOfGo/methods/exercise-errors.go) | ✔️ | ✔️ | ❌ | ❌ |
| [TourOfGo/methods/exercise-images.go](tests/TourOfGo/methods/exercise-images.go) | ✔️ | ❌ | ❌ | ❌ |
| [TourOfGo/methods/exercise-reader.go](tests/TourOfGo/methods/exercise-reader.go) | ✔️ | ❌ | ❌ | ❌ |
| [TourOfGo/methods/exercise-rot-reader.go](tests/TourOfGo/methods/exercise-rot-reader.go) | ✔️ | ❌ | ❌ | ❌ |
| [TourOfGo/methods/exercise-stringer.go](tests/TourOfGo/methods/exercise-stringer.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/methods/exercise-stringer.cpp)) | ❌ |
| [TourOfGo/methods/images.go](tests/TourOfGo/methods/images.go) | ✔️ | ❌ | ❌ | ❌ |
| [TourOfGo/methods/indirection.go](tests/TourOfGo/methods/indirection.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/methods/indirection.cpp)) | ❌ |
| [TourOfGo/methods/indirection-values.go](tests/TourOfGo/methods/indirection-values.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/methods/indirection-values.cpp)) | ❌ |
| [TourOfGo/methods/inline-interface.go](tests/TourOfGo/methods/inline-interface.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/methods/inline-interface.cpp)) | ❌ |
| [TourOfGo/methods/interfaces.go](tests/TourOfGo/methods/interfaces.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/methods/interfaces.cpp)) | ❌ |
| [TourOfGo/methods/interfaces-are-satisfied-implicitly.go](tests/TourOfGo/methods/interfaces-are-satisfied-implicitly.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/methods/interfaces-are-satisfied-implicitly.cpp)) | ✔️ |
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
| file | cpp generate |
| ---- | -------------| 
| $(ImportDir)/bufio/bufio.go | ✔️ ([cpp](generated/golang/bufio/bufio.cpp), [h](generated/golang/bufio/bufio.h))|
| $(ImportDir)/bytes/bytes.go | ❌ |
| $(ImportDir)/cmp/cmp.go | ✔️ ([cpp](generated/golang/cmp/cmp.cpp), [h](generated/golang/cmp/cmp.h))|
| $(ImportDir)/compress/flate/deflate.go | ❌ |
| $(ImportDir)/compress/flate/inflate.go | ❌ |
| $(ImportDir)/compress/zlib/reader.go | ✔️ ([cpp](generated/golang/compress/zlib/reader.cpp), [h](generated/golang/compress/zlib/reader.h))|
| $(ImportDir)/compress/zlib/writer.go | ✔️ ([cpp](generated/golang/compress/zlib/writer.cpp), [h](generated/golang/compress/zlib/writer.h))|
| $(ImportDir)/encoding/base64/base64.go | ❌ |
| $(ImportDir)/encoding/binary/binary.go | ✔️ ([cpp](generated/golang/encoding/binary/binary.cpp), [h](generated/golang/encoding/binary/binary.h))|
| $(ImportDir)/encoding/binary/native_endian_little.go | ✔️ ([cpp](generated/golang/encoding/binary/native_endian_little.cpp), [h](generated/golang/encoding/binary/native_endian_little.h))|
| $(ImportDir)/errors/errors.go | ✔️ ([cpp](generated/golang/errors/errors.cpp), [h](generated/golang/errors/errors.h))|
| $(ImportDir)/fmt/errors.go | ✔️ ([cpp](generated/golang/fmt/errors.cpp), [h](generated/golang/fmt/errors.h))|
| $(ImportDir)/fmt/print.go | ❌ |
| $(ImportDir)/golang.org/x/tour/pic/pic.go | ✔️ ([cpp](generated/golang/golang.org/x/tour/pic/pic.cpp), [h](generated/golang/golang.org/x/tour/pic/pic.h))|
| $(ImportDir)/golang.org/x/tour/reader/validate.go | ✔️ ([cpp](generated/golang/golang.org/x/tour/reader/validate.cpp), [h](generated/golang/golang.org/x/tour/reader/validate.h))|
| $(ImportDir)/golang.org/x/tour/tree/tree.go | ✔️ ([cpp](generated/golang/golang.org/x/tour/tree/tree.cpp), [h](generated/golang/golang.org/x/tour/tree/tree.h))|
| $(ImportDir)/golang.org/x/tour/wc/wc.go | ✔️ ([cpp](generated/golang/golang.org/x/tour/wc/wc.cpp), [h](generated/golang/golang.org/x/tour/wc/wc.h))|
| $(ImportDir)/hash/adler32/adler32.go | ✔️ ([cpp](generated/golang/hash/adler32/adler32.cpp), [h](generated/golang/hash/adler32/adler32.h))|
| $(ImportDir)/hash/crc32/crc32.go | ✔️ ([cpp](generated/golang/hash/crc32/crc32.cpp), [h](generated/golang/hash/crc32/crc32.h))|
| $(ImportDir)/hash/crc32/crc32_amd64.go | ✔️ ([cpp](generated/golang/hash/crc32/crc32_amd64.cpp), [h](generated/golang/hash/crc32/crc32_amd64.h))|
| $(ImportDir)/hash/crc32/crc32_generic.go | ✔️ ([cpp](generated/golang/hash/crc32/crc32_generic.cpp), [h](generated/golang/hash/crc32/crc32_generic.h))|
| $(ImportDir)/hash/hash.go | ✔️ ([cpp](generated/golang/hash/hash.cpp), [h](generated/golang/hash/hash.h))|
| $(ImportDir)/image/color/color.go | ✔️ ([cpp](generated/golang/image/color/color.cpp), [h](generated/golang/image/color/color.h))|
| $(ImportDir)/image/format.go | ✔️ ([cpp](generated/golang/image/format.cpp), [h](generated/golang/image/format.h))|
| $(ImportDir)/image/geom.go | ✔️ ([cpp](generated/golang/image/geom.cpp), [h](generated/golang/image/geom.h))|
| $(ImportDir)/image/image.go | ❌ |
| $(ImportDir)/image/png/paeth.go | ✔️ ([cpp](generated/golang/image/png/paeth.cpp), [h](generated/golang/image/png/paeth.h))|
| $(ImportDir)/image/png/reader.go | ✔️ ([cpp](generated/golang/image/png/reader.cpp), [h](generated/golang/image/png/reader.h))|
| $(ImportDir)/image/png/writer.go | ✔️ ([cpp](generated/golang/image/png/writer.cpp), [h](generated/golang/image/png/writer.h))|
| $(ImportDir)/internal/abi/abi.go | ✔️ ([cpp](generated/golang/internal/abi/abi.cpp), [h](generated/golang/internal/abi/abi.h))|
| $(ImportDir)/internal/abi/abi_amd64.go | ✔️ ([cpp](generated/golang/internal/abi/abi_amd64.cpp), [h](generated/golang/internal/abi/abi_amd64.h))|
| $(ImportDir)/internal/abi/funcpc.go | ✔️ ([cpp](generated/golang/internal/abi/funcpc.cpp), [h](generated/golang/internal/abi/funcpc.h))|
| $(ImportDir)/internal/abi/symtab.go | ✔️ ([cpp](generated/golang/internal/abi/symtab.cpp), [h](generated/golang/internal/abi/symtab.h))|
| $(ImportDir)/internal/abi/type.go | ❌ |
| $(ImportDir)/internal/bytealg/bytealg.go | ✔️ ([cpp](generated/golang/internal/bytealg/bytealg.cpp), [h](generated/golang/internal/bytealg/bytealg.h))|
| $(ImportDir)/internal/chacha8rand/chacha8.go | ✔️ ([cpp](generated/golang/internal/chacha8rand/chacha8.cpp), [h](generated/golang/internal/chacha8rand/chacha8.h))|
| $(ImportDir)/internal/cpu/cpu.go | ❌ |
| $(ImportDir)/internal/goarch/goarch.go | ✔️ ([cpp](generated/golang/internal/goarch/goarch.cpp), [h](generated/golang/internal/goarch/goarch.h))|
| $(ImportDir)/internal/goarch/goarch_amd64.go | ✔️ ([cpp](generated/golang/internal/goarch/goarch_amd64.cpp), [h](generated/golang/internal/goarch/goarch_amd64.h))|
| $(ImportDir)/internal/goarch/zgoarch_amd64.go | ✔️ ([cpp](generated/golang/internal/goarch/zgoarch_amd64.cpp), [h](generated/golang/internal/goarch/zgoarch_amd64.h))|
| $(ImportDir)/internal/goexperiment/exp_allocheaders_on.go | ✔️ ([cpp](generated/golang/internal/goexperiment/exp_allocheaders_on.cpp), [h](generated/golang/internal/goexperiment/exp_allocheaders_on.h))|
| $(ImportDir)/internal/goexperiment/exp_cgocheck2_off.go | ✔️ ([cpp](generated/golang/internal/goexperiment/exp_cgocheck2_off.cpp), [h](generated/golang/internal/goexperiment/exp_cgocheck2_off.h))|
| $(ImportDir)/internal/goexperiment/exp_heapminimum512kib_off.go | ✔️ ([cpp](generated/golang/internal/goexperiment/exp_heapminimum512kib_off.cpp), [h](generated/golang/internal/goexperiment/exp_heapminimum512kib_off.h))|
| $(ImportDir)/internal/goos/zgoos_windows.go | ✔️ ([cpp](generated/golang/internal/goos/zgoos_windows.cpp), [h](generated/golang/internal/goos/zgoos_windows.h))|
| $(ImportDir)/internal/race/norace.go | ✔️ ([cpp](generated/golang/internal/race/norace.cpp), [h](generated/golang/internal/race/norace.h))|
| $(ImportDir)/io/io.go | ✔️ ([cpp](generated/golang/io/io.cpp), [h](generated/golang/io/io.h))|
| $(ImportDir)/math/abs.go | ✔️ ([cpp](generated/golang/math/abs.cpp), [h](generated/golang/math/abs.h))|
| $(ImportDir)/math/bits.go | ✔️ ([cpp](generated/golang/math/bits.cpp), [h](generated/golang/math/bits.h))|
| $(ImportDir)/math/bits/bits.go | ✔️ ([cpp](generated/golang/math/bits/bits.cpp), [h](generated/golang/math/bits/bits.h))|
| $(ImportDir)/math/bits/bits_tables.go | ✔️ ([cpp](generated/golang/math/bits/bits_tables.cpp), [h](generated/golang/math/bits/bits_tables.h))|
| $(ImportDir)/math/cmplx/sqrt.go | ✔️ ([cpp](generated/golang/math/cmplx/sqrt.cpp), [h](generated/golang/math/cmplx/sqrt.h))|
| $(ImportDir)/math/const.go | ✔️ ([cpp](generated/golang/math/const.cpp), [h](generated/golang/math/const.h))|
| $(ImportDir)/math/copysign.go | ✔️ ([cpp](generated/golang/math/copysign.cpp), [h](generated/golang/math/copysign.h))|
| $(ImportDir)/math/exp.go | ✔️ ([cpp](generated/golang/math/exp.cpp), [h](generated/golang/math/exp.h))|
| $(ImportDir)/math/exp2_noasm.go | ✔️ ([cpp](generated/golang/math/exp2_noasm.cpp), [h](generated/golang/math/exp2_noasm.h))|
| $(ImportDir)/math/exp_asm.go | ✔️ ([cpp](generated/golang/math/exp_asm.cpp), [h](generated/golang/math/exp_asm.h))|
| $(ImportDir)/math/frexp.go | ✔️ ([cpp](generated/golang/math/frexp.cpp), [h](generated/golang/math/frexp.h))|
| $(ImportDir)/math/hypot.go | ✔️ ([cpp](generated/golang/math/hypot.cpp), [h](generated/golang/math/hypot.h))|
| $(ImportDir)/math/hypot_asm.go | ✔️ ([cpp](generated/golang/math/hypot_asm.cpp), [h](generated/golang/math/hypot_asm.h))|
| $(ImportDir)/math/ldexp.go | ✔️ ([cpp](generated/golang/math/ldexp.cpp), [h](generated/golang/math/ldexp.h))|
| $(ImportDir)/math/log.go | ✔️ ([cpp](generated/golang/math/log.cpp), [h](generated/golang/math/log.h))|
| $(ImportDir)/math/log_asm.go | ✔️ ([cpp](generated/golang/math/log_asm.cpp), [h](generated/golang/math/log_asm.h))|
| $(ImportDir)/math/modf.go | ✔️ ([cpp](generated/golang/math/modf.cpp), [h](generated/golang/math/modf.h))|
| $(ImportDir)/math/modf_noasm.go | ✔️ ([cpp](generated/golang/math/modf_noasm.cpp), [h](generated/golang/math/modf_noasm.h))|
| $(ImportDir)/math/pow.go | ✔️ ([cpp](generated/golang/math/pow.cpp), [h](generated/golang/math/pow.h))|
| $(ImportDir)/math/rand/rand.go | ❌ |
| $(ImportDir)/math/signbit.go | ✔️ ([cpp](generated/golang/math/signbit.cpp), [h](generated/golang/math/signbit.h))|
| $(ImportDir)/math/sqrt.go | ✔️ ([cpp](generated/golang/math/sqrt.cpp), [h](generated/golang/math/sqrt.h))|
| $(ImportDir)/math/stubs.go | ✔️ ([cpp](generated/golang/math/stubs.cpp), [h](generated/golang/math/stubs.h))|
| $(ImportDir)/math/unsafe.go | ✔️ ([cpp](generated/golang/math/unsafe.cpp), [h](generated/golang/math/unsafe.h))|
| $(ImportDir)/reflect/type.go | ❌ |
| $(ImportDir)/reflect/value.go | ❌ |
| $(ImportDir)/runtime/asan0.go | ✔️ ([cpp](generated/golang/runtime/asan0.cpp), [h](generated/golang/runtime/asan0.h))|
| $(ImportDir)/runtime/atomic_pointer.go | ✔️ ([cpp](generated/golang/runtime/atomic_pointer.cpp), [h](generated/golang/runtime/atomic_pointer.h))|
| $(ImportDir)/runtime/cgocall.go | ✔️ ([cpp](generated/golang/runtime/cgocall.cpp), [h](generated/golang/runtime/cgocall.h))|
| $(ImportDir)/runtime/cgocheck.go | ✔️ ([cpp](generated/golang/runtime/cgocheck.cpp), [h](generated/golang/runtime/cgocheck.h))|
| $(ImportDir)/runtime/debug.go | ✔️ ([cpp](generated/golang/runtime/debug.cpp), [h](generated/golang/runtime/debug.h))|
| $(ImportDir)/runtime/env_posix.go | ✔️ ([cpp](generated/golang/runtime/env_posix.cpp), [h](generated/golang/runtime/env_posix.h))|
| $(ImportDir)/runtime/error.go | ❌ |
| $(ImportDir)/runtime/extern.go | ✔️ ([cpp](generated/golang/runtime/extern.cpp), [h](generated/golang/runtime/extern.h))|
| $(ImportDir)/runtime/float.go | ✔️ ([cpp](generated/golang/runtime/float.cpp), [h](generated/golang/runtime/float.h))|
| $(ImportDir)/runtime/iface.go | ❌ |
| $(ImportDir)/runtime/internal/atomic/atomic_amd64.go | ✔️ ([cpp](generated/golang/runtime/internal/atomic/atomic_amd64.cpp), [h](generated/golang/runtime/internal/atomic/atomic_amd64.h))|
| $(ImportDir)/runtime/internal/atomic/stubs.go | ✔️ ([cpp](generated/golang/runtime/internal/atomic/stubs.cpp), [h](generated/golang/runtime/internal/atomic/stubs.h))|
| $(ImportDir)/runtime/internal/atomic/types.go | ❌ |
| $(ImportDir)/runtime/internal/math/math.go | ✔️ ([cpp](generated/golang/runtime/internal/math/math.cpp), [h](generated/golang/runtime/internal/math/math.h))|
| $(ImportDir)/runtime/internal/sys/consts.go | ✔️ ([cpp](generated/golang/runtime/internal/sys/consts.cpp), [h](generated/golang/runtime/internal/sys/consts.h))|
| $(ImportDir)/runtime/internal/sys/consts_norace.go | ✔️ ([cpp](generated/golang/runtime/internal/sys/consts_norace.cpp), [h](generated/golang/runtime/internal/sys/consts_norace.h))|
| $(ImportDir)/runtime/internal/sys/intrinsics.go | ✔️ ([cpp](generated/golang/runtime/internal/sys/intrinsics.cpp), [h](generated/golang/runtime/internal/sys/intrinsics.h))|
| $(ImportDir)/runtime/internal/sys/nih.go | ✔️ ([cpp](generated/golang/runtime/internal/sys/nih.cpp), [h](generated/golang/runtime/internal/sys/nih.h))|
| $(ImportDir)/runtime/lfstack.go | ❌ |
| $(ImportDir)/runtime/lock_sema.go | ❌ |
| $(ImportDir)/runtime/lockrank.go | ✔️ ([cpp](generated/golang/runtime/lockrank.cpp), [h](generated/golang/runtime/lockrank.h))|
| $(ImportDir)/runtime/lockrank_off.go | ✔️ ([cpp](generated/golang/runtime/lockrank_off.cpp), [h](generated/golang/runtime/lockrank_off.h))|
| $(ImportDir)/runtime/malloc.go | ❌ |
| $(ImportDir)/runtime/map.go | ❌ |
| $(ImportDir)/runtime/mbitmap.go | ❌ |
| $(ImportDir)/runtime/mbitmap_allocheaders.go | ✔️ ([cpp](generated/golang/runtime/mbitmap_allocheaders.cpp), [h](generated/golang/runtime/mbitmap_allocheaders.h))|
| $(ImportDir)/runtime/mcache.go | ✔️ ([cpp](generated/golang/runtime/mcache.cpp), [h](generated/golang/runtime/mcache.h))|
| $(ImportDir)/runtime/mcentral.go | ❌ |
| $(ImportDir)/runtime/mem.go | ✔️ ([cpp](generated/golang/runtime/mem.cpp), [h](generated/golang/runtime/mem.h))|
| $(ImportDir)/runtime/mem_windows.go | ✔️ ([cpp](generated/golang/runtime/mem_windows.cpp), [h](generated/golang/runtime/mem_windows.h))|
| $(ImportDir)/runtime/mfinal.go | ❌ |
| $(ImportDir)/runtime/mfixalloc.go | ✔️ ([cpp](generated/golang/runtime/mfixalloc.cpp), [h](generated/golang/runtime/mfixalloc.h))|
| $(ImportDir)/runtime/mgc.go | ❌ |
| $(ImportDir)/runtime/mgclimit.go | ❌ |
| $(ImportDir)/runtime/mgcmark.go | ❌ |
| $(ImportDir)/runtime/mgcpacer.go | ✔️ ([cpp](generated/golang/runtime/mgcpacer.cpp), [h](generated/golang/runtime/mgcpacer.h))|
| $(ImportDir)/runtime/mgcscavenge.go | ✔️ ([cpp](generated/golang/runtime/mgcscavenge.cpp), [h](generated/golang/runtime/mgcscavenge.h))|
| $(ImportDir)/runtime/mgcsweep.go | ❌ |
| $(ImportDir)/runtime/mgcwork.go | ✔️ ([cpp](generated/golang/runtime/mgcwork.cpp), [h](generated/golang/runtime/mgcwork.h))|
| $(ImportDir)/runtime/mheap.go | ❌ |
| $(ImportDir)/runtime/mpagealloc.go | ❌ |
| $(ImportDir)/runtime/mpagealloc_64bit.go | ✔️ ([cpp](generated/golang/runtime/mpagealloc_64bit.cpp), [h](generated/golang/runtime/mpagealloc_64bit.h))|
| $(ImportDir)/runtime/mpallocbits.go | ❌ |
| $(ImportDir)/runtime/mranges.go | ✔️ ([cpp](generated/golang/runtime/mranges.cpp), [h](generated/golang/runtime/mranges.h))|
| $(ImportDir)/runtime/msan0.go | ✔️ ([cpp](generated/golang/runtime/msan0.cpp), [h](generated/golang/runtime/msan0.h))|
| $(ImportDir)/runtime/msize_allocheaders.go | ✔️ ([cpp](generated/golang/runtime/msize_allocheaders.cpp), [h](generated/golang/runtime/msize_allocheaders.h))|
| $(ImportDir)/runtime/mspanset.go | ❌ |
| $(ImportDir)/runtime/mstats.go | ✔️ ([cpp](generated/golang/runtime/mstats.cpp), [h](generated/golang/runtime/mstats.h))|
| $(ImportDir)/runtime/mwbbuf.go | ✔️ ([cpp](generated/golang/runtime/mwbbuf.cpp), [h](generated/golang/runtime/mwbbuf.h))|
| $(ImportDir)/runtime/os_windows.go | ❌ |
| $(ImportDir)/runtime/pagetrace_off.go | ✔️ ([cpp](generated/golang/runtime/pagetrace_off.cpp), [h](generated/golang/runtime/pagetrace_off.h))|
| $(ImportDir)/runtime/panic.go | ❌ |
| $(ImportDir)/runtime/pinner.go | ❌ |
| $(ImportDir)/runtime/plugin.go | ✔️ ([cpp](generated/golang/runtime/plugin.cpp), [h](generated/golang/runtime/plugin.h))|
| $(ImportDir)/runtime/print.go | ✔️ ([cpp](generated/golang/runtime/print.cpp), [h](generated/golang/runtime/print.h))|
| $(ImportDir)/runtime/proc.go | ❌ |
| $(ImportDir)/runtime/race0.go | ✔️ ([cpp](generated/golang/runtime/race0.cpp), [h](generated/golang/runtime/race0.h))|
| $(ImportDir)/runtime/rand.go | ✔️ ([cpp](generated/golang/runtime/rand.cpp), [h](generated/golang/runtime/rand.h))|
| $(ImportDir)/runtime/runtime.go | ❌ |
| $(ImportDir)/runtime/runtime1.go | ❌ |
| $(ImportDir)/runtime/runtime2.go | ❌ |
| $(ImportDir)/runtime/sizeclasses.go | ✔️ ([cpp](generated/golang/runtime/sizeclasses.cpp), [h](generated/golang/runtime/sizeclasses.h))|
| $(ImportDir)/runtime/slice.go | ✔️ ([cpp](generated/golang/runtime/slice.cpp), [h](generated/golang/runtime/slice.h))|
| $(ImportDir)/runtime/stack.go | ❌ |
| $(ImportDir)/runtime/stkframe.go | ✔️ ([cpp](generated/golang/runtime/stkframe.cpp), [h](generated/golang/runtime/stkframe.h))|
| $(ImportDir)/runtime/string.go | ❌ |
| $(ImportDir)/runtime/stubs.go | ✔️ ([cpp](generated/golang/runtime/stubs.cpp), [h](generated/golang/runtime/stubs.h))|
| $(ImportDir)/runtime/stubs3.go | ✔️ ([cpp](generated/golang/runtime/stubs3.cpp), [h](generated/golang/runtime/stubs3.h))|
| $(ImportDir)/runtime/symtab.go | ✔️ ([cpp](generated/golang/runtime/symtab.cpp), [h](generated/golang/runtime/symtab.h))|
| $(ImportDir)/runtime/symtabinl.go | ✔️ ([cpp](generated/golang/runtime/symtabinl.cpp), [h](generated/golang/runtime/symtabinl.h))|
| $(ImportDir)/runtime/time.go | ❌ |
| $(ImportDir)/runtime/time_nofake.go | ✔️ ([cpp](generated/golang/runtime/time_nofake.cpp), [h](generated/golang/runtime/time_nofake.h))|
| $(ImportDir)/runtime/trace2runtime.go | ❌ |
| $(ImportDir)/runtime/traceback.go | ❌ |
| $(ImportDir)/runtime/type.go | ❌ |
| $(ImportDir)/runtime/typekind.go | ✔️ ([cpp](generated/golang/runtime/typekind.cpp), [h](generated/golang/runtime/typekind.h))|
| $(ImportDir)/runtime/write_err.go | ✔️ ([cpp](generated/golang/runtime/write_err.cpp), [h](generated/golang/runtime/write_err.h))|
| $(ImportDir)/slices/sort.go | ✔️ ([cpp](generated/golang/slices/sort.cpp), [h](generated/golang/slices/sort.h))|
| $(ImportDir)/slices/zsortanyfunc.go | ✔️ ([cpp](generated/golang/slices/zsortanyfunc.cpp), [h](generated/golang/slices/zsortanyfunc.h))|
| $(ImportDir)/slices/zsortordered.go | ✔️ ([cpp](generated/golang/slices/zsortordered.cpp), [h](generated/golang/slices/zsortordered.h))|
| $(ImportDir)/sort/sort.go | ✔️ ([cpp](generated/golang/sort/sort.cpp), [h](generated/golang/sort/sort.h))|
| $(ImportDir)/sort/sort_impl_go121.go | ✔️ ([cpp](generated/golang/sort/sort_impl_go121.cpp), [h](generated/golang/sort/sort_impl_go121.h))|
| $(ImportDir)/sort/zsortinterface.go | ✔️ ([cpp](generated/golang/sort/zsortinterface.cpp), [h](generated/golang/sort/zsortinterface.h))|
| $(ImportDir)/strconv/itoa.go | ✔️ ([cpp](generated/golang/strconv/itoa.cpp), [h](generated/golang/strconv/itoa.h))|
| $(ImportDir)/strings/builder.go | ✔️ ([cpp](generated/golang/strings/builder.cpp), [h](generated/golang/strings/builder.h))|
| $(ImportDir)/strings/reader.go | ✔️ ([cpp](generated/golang/strings/reader.cpp), [h](generated/golang/strings/reader.h))|
| $(ImportDir)/strings/strings.go | ❌ |
| $(ImportDir)/sync/atomic/doc.go | ✔️ ([cpp](generated/golang/sync/atomic/doc.cpp), [h](generated/golang/sync/atomic/doc.h))|
| $(ImportDir)/sync/atomic/type.go | ❌ |
| $(ImportDir)/sync/atomic/value.go | ✔️ ([cpp](generated/golang/sync/atomic/value.cpp), [h](generated/golang/sync/atomic/value.h))|
| $(ImportDir)/sync/cond.go | ✔️ ([cpp](generated/golang/sync/cond.cpp), [h](generated/golang/sync/cond.h))|
| $(ImportDir)/sync/map.go | ❌ |
| $(ImportDir)/sync/mutex.go | ✔️ ([cpp](generated/golang/sync/mutex.cpp), [h](generated/golang/sync/mutex.h))|
| $(ImportDir)/sync/once.go | ✔️ ([cpp](generated/golang/sync/once.cpp), [h](generated/golang/sync/once.h))|
| $(ImportDir)/sync/pool.go | ✔️ ([cpp](generated/golang/sync/pool.cpp), [h](generated/golang/sync/pool.h))|
| $(ImportDir)/sync/poolqueue.go | ✔️ ([cpp](generated/golang/sync/poolqueue.cpp), [h](generated/golang/sync/poolqueue.h))|
| $(ImportDir)/sync/runtime.go | ✔️ ([cpp](generated/golang/sync/runtime.cpp), [h](generated/golang/sync/runtime.h))|
| $(ImportDir)/sync/runtime2.go | ✔️ ([cpp](generated/golang/sync/runtime2.cpp), [h](generated/golang/sync/runtime2.h))|
| $(ImportDir)/time/sleep.go | ❌ |
| $(ImportDir)/time/tick.go | ✔️ ([cpp](generated/golang/time/tick.cpp), [h](generated/golang/time/tick.h))|
| $(ImportDir)/time/time.go | ❌ |
| $(ImportDir)/unicode/utf8/utf8.go | ❌ |
| $(ImportDir)/unsafe/unsafe.go | ✔️ ([cpp](generated/golang/unsafe/unsafe.cpp), [h](generated/golang/unsafe/unsafe.h))|
