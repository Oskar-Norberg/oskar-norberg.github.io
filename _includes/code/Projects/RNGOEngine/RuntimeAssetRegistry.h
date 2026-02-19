class RuntimeAssetRegistry : public Utilities::Singleton<RuntimeAssetRegistry>
{
public:
    RuntimeAssetRegistry();

    template<Concepts::DerivedFrom<Asset> TAsset>
    AssetRegistryEntry& Insert(const AssetHandle& handle, TAsset&& asset);

    void Remove(AssetType type, AssetHandle handle);

    AssetState GetState(AssetType type, const AssetHandle& handle) const;
    void SetState(AssetType type, const AssetHandle& handle, AssetState state);

    template<Concepts::DerivedFrom<Asset> TAsset>
    std::optional<std::reference_wrapper<TAsset>> TryGet(AssetHandle handle);

    template<Concepts::DerivedFrom<Asset> TAsset>
    std::optional<std::reference_wrapper<const TAsset>> TryGet(AssetHandle handle) const;

private:
    std::tuple<
        std::monostate,           // Placeholder for None
        AssetMap<ModelAsset>,     // Models
        AssetMap<TextureAsset>,   // Textures
        AssetMap<ShaderAsset>,    // Shaders
        AssetMap<MaterialAsset>,  // Materials
        std::monostate            // Placeholder for Count
    > m_assetStorage;
};