class Asset
{
public:
    explicit Asset(AssetHandle&& handle)
        : m_handle(std::move(handle))
    {
    }

    virtual ~Asset() = default;

public:
    AssetType GetType() const;
    bool IsType(AssetType type) const;

    // TODO: Unsafe as all hell.
    template<Concepts::DerivedFrom<Asset> TAsset>
    TAsset& GetAsType()
    {
        return static_cast<TAsset&>(*this);
    }

    template<Concepts::DerivedFrom<Asset> TAsset>
    const TAsset& GetAsType() const
    {
        return static_cast<const TAsset&>(*this);
    }

    const AssetHandle& GetHandle() const
    {
        return m_handle;
    }

public:
    AssetState GetState() const;
    bool IsReady() const;

private:
    AssetHandle m_handle;
};