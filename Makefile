# ============================================================
# CampusGuard Makefile
# COS214 Practical 5 - Emergency Response Coordination
# ============================================================
# Builds the complete CampusGuard application using C++11.
# Usage: make          -> builds ./campusguard
#        make clean    -> removes build artefacts
#        make run      -> builds and runs
# ============================================================

CXX      := g++
CXXFLAGS := -std=c++11 -Wall -Wextra -Wpedantic -g -O0 \
            -fno-omit-frame-pointer -fstack-protector-strong
LDFLAGS  :=
TARGET   := campusguard
BUILD    := build

# All source files (headers are discovered automatically by dependency tracking)
SRCS := $(wildcard *.cpp)

OBJS := $(patsubst %.cpp,$(BUILD)/%.o,$(SRCS))
DEPS := $(OBJS:.o=.d)

# ============================================================
# Default target
# ============================================================
.PHONY: all
all: $(TARGET)

# ============================================================
# Link
# ============================================================
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@ $(LDFLAGS)
	@echo "=================================================="
	@echo " Build complete: ./$(TARGET)"
	@echo "=================================================="

# ============================================================
# Compile + auto-generate header dependencies
# ============================================================
$(BUILD)/%.o: %.cpp | $(BUILD)
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

$(BUILD):
	@mkdir -p $(BUILD)

# ============================================================
# Convenience targets
# ============================================================
.PHONY: run
run: all
	./$(TARGET)

.PHONY: valgrind
valgrind: all
	valgrind --leak-check=full --show-leak-kinds=all \
	         --track-origins=yes --error-exitcode=1 \
	         ./$(TARGET)

.PHONY: clean
clean:
	rm -rf $(BUILD) $(TARGET)
	@echo "Cleaned."

# ============================================================
# Include auto-generated dependency files
# ============================================================
-include $(DEPS)