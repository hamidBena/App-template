#pragma once
#include <random>
#include <sstream>
#include <iomanip>
#include <string>
#include <cstdint>

namespace core {

    class UUID {
    public:
        UUID() {
            static thread_local std::mt19937_64 gen(std::random_device{}());
            uint64_t high = gen();
            uint64_t low  = gen();
            m_id = (static_cast<__uint128_t>(high) << 64) | low;
        }

        UUID(const UUID& other) = default;
        UUID& operator=(const UUID& other) = default;

        bool operator==(const UUID& other) const noexcept {
            return m_id == other.m_id;
        }

        bool operator!=(const UUID& other) const noexcept {
            return !(*this == other);
        }

        /// Converts the UUID to a 32-character hexadecimal string
        std::string toString() const {
            uint64_t high = static_cast<uint64_t>(m_id >> 64);
            uint64_t low  = static_cast<uint64_t>(m_id & 0xFFFFFFFFFFFFFFFFULL);

            std::ostringstream oss;
            oss << std::hex << std::setfill('0')
                << std::setw(16) << high
                << std::setw(16) << low;

            return oss.str();
        }

        /// Expose the raw 128-bit value (if needed)
        __uint128_t value() const noexcept { return m_id; }

    private:
        __uint128_t m_id;
    };

} // namespace core

// Optional: enable use as a key in unordered_map / unordered_set
namespace std {
    template<>
    struct hash<core::UUID> {
        std::size_t operator()(const core::UUID& uuid) const noexcept {
            auto id = uuid.value();
            // Mix high and low 64 bits
            return static_cast<std::size_t>(
                (id >> 64) ^ (id & 0xFFFFFFFFFFFFFFFFULL)
            );
        }
    };
}
