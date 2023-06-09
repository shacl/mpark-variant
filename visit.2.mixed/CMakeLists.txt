# MPark.Variant
#
# Copyright Michael Park, 2015-2017
#
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

set(test "visit.2.mixed")
set(repeat 2)

set(title "Double visitation - Mixed variants (${repeat}x)")
set(xlabel "Number of alternatives")

set(range "(1...5).to_a + (5..25).step(5).to_a")

set(datasets)
add_compile_benchmark(datasets anthonyw ${test} ${repeat} ${range})
add_compile_benchmark(datasets boost    ${test} ${repeat} ${range})
add_compile_benchmark(datasets eggs     ${test} ${repeat} ${range})
add_compile_benchmark(datasets juice    ${test} ${repeat} ${range})
add_compile_benchmark(datasets mpark    ${test} ${repeat} ${range})
add_compile_benchmark(datasets pdimov   ${test} ${repeat} ${range})
add_compile_benchmark(datasets std      ${test} ${repeat} ${range})

# Add a binary size chart
metabench_add_chart(
  chart.binary_size.${test}
  ALL
  ASPECT EXECUTABLE_SIZE
  TITLE ${title}
  XLABEL ${xlabel}
  DATASETS ${datasets}
  OUTPUT binary_size.html
)

# Add a compile time chart
metabench_add_chart(
  chart.compile_time.${test}
  ALL
  ASPECT COMPILATION_TIME
  TITLE ${title}
  XLABEL ${xlabel}
  DATASETS ${datasets}
  OUTPUT compile_time.html
)
