# Results on test directory

| file | cpp generate | cpp compilation | run | result diff |
| ---- | ------------ | --------------- | --- | ----------- |
| [HelloWorld.go](tests/HelloWorld.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/HelloWorld.cpp)) | ❌ |
| [TourOfGo/basics/basic-types.go](tests/TourOfGo/basics/basic-types.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/basics/basic-types.cpp)) | ❌ |
| [TourOfGo/basics/constants.go](tests/TourOfGo/basics/constants.go) | ✔️ | ✔️ | ✔️ ([cpp](generated/tests/TourOfGo/basics/constants.cpp)) | ❌ |
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
