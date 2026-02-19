template<typename TSystemContext>
class ISystem
{
public:
    virtual ~ISystem() = default;

    virtual void Initialize(Core::World& world, TSystemContext& context)
    {
    }

    virtual void Update(Core::World& world, TSystemContext& context)
    {
    }

    virtual void Exit(Core::World& world, TSystemContext& context)
    {
    }

    std::string_view GetName() const
    {
        return m_debugName;
    }

protected:
    std::string_view m_debugName;
};