// 64-bit wide UUID.
class UUID
{
public:
    explicit UUID(std::uint64_t value);
    // NOTE: Default constructs to zero UUID. Make sure this is your intention. Use GenerateUUID() to get a random UUID.
    UUID();

    ~UUID();
    UUID(const UUID& other);
    UUID& operator=(const UUID& other);
    UUID(UUID&& other) noexcept;
    UUID& operator=(UUID&& other) noexcept;

    bool operator==(const UUID& other) const;

    std::uint64_t GetValue() const
    {
        return m_uuid;
    }

    explicit constexpr operator uint64_t() const
    {
        return m_uuid;
    }

private:
    std::uint64_t m_uuid;
};