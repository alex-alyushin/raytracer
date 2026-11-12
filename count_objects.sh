#!/bin/bash

# Script to count object creations from callgrind output

CALLGRIND_FILE="${1:-callgrind.out.2746}"

echo "========================================="
echo "   Object Creation Statistics"
echo "========================================="
echo "Analyzing: $CALLGRIND_FILE"
echo ""

# Function to count constructor calls
count_pattern() {
    local pattern="$1"
    local name="$2"
    local count=$(callgrind_annotate "$CALLGRIND_FILE" 2>/dev/null | \
                  grep "$pattern" | \
                  grep -oE "\([0-9,]+x\)" | \
                  sed 's/[(),x]//g' | \
                  awk '{sum += $1} END {print sum+0}')
    printf "%-20s %'15d\n" "$name:" "$count"
}

# Count vec constructors
echo "=== Constructors ==="
count_pattern "vec::vec(double" "vec"
count_pattern "intersection::intersection()" "intersection"
count_pattern "ray::ray(vec const&" "ray"

echo ""
echo "=== Hit methods (for reference) ==="

# Triangle hit count
tri_hit=$(callgrind_annotate "$CALLGRIND_FILE" 2>/dev/null | \
          grep "triangle::hit" | head -1 | \
          grep -oE "\([0-9,]+x\)" | \
          sed 's/[(),x]//g' | awk '{print $1+0}')
printf "%-20s %'15d\n" "triangle::hit:" "$tri_hit"

# Sphere hit count
sph_hit=$(callgrind_annotate "$CALLGRIND_FILE" 2>/dev/null | \
          grep "sphere::hit" | head -1 | \
          grep -oE "\([0-9,]+x\)" | \
          sed 's/[(),x]//g' | awk '{print $1+0}')
printf "%-20s %'15d\n" "sphere::hit:" "$sph_hit"

echo ""
echo "=== Top functions by instruction count ==="
callgrind_annotate "$CALLGRIND_FILE" 2>/dev/null | \
    grep -E "vec::|intersection::|ray::|triangle::|sphere::" | \
    head -10

echo ""
echo "========================================="
