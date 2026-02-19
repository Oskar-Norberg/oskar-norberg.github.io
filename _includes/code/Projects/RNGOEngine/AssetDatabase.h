class AssetDatabase : public Utilities::Singleton<AssetDatabase>
{
public:
    AssetDatabase();

    // Instead of templated functions?
    // Register / Unregister
public:
    void RegisterAsset(AssetType type, std::unique_ptr<AssetMetadata> metadata);

    void UnregisterAsset(const AssetHandle& uuid);

    // State
public:
    bool IsRegistered(const AssetHandle& handle) const;
    bool IsRegistered(const std::filesystem::path& path) const;
    
    // Unchecked
    AssetHandle GetAssetHandle(const std::filesystem::path& path) const;

    AssetMetadata& GetAssetMetadata(const AssetHandle& handle);

    const AssetMetadata& GetAssetMetadata(const AssetHandle& handle) const;

    // Checked
    std::optional<AssetHandle> TryGetAssetHandle(const std::filesystem::path& path) const;

    std::optional<std::reference_wrapper<AssetMetadata>> TryGetAssetMetadata(const AssetHandle& handle);

    std::optional<std::reference_wrapper<const AssetMetadata>> TryGetAssetMetadata(
        const AssetHandle& handle) const;

private:
    std::unordered_map<AssetType, std::unique_ptr<AssetMetadataStorage>> m_metadataStorages;
    std::unordered_map<AssetHandle, std::pair<AssetType, size_t>> m_handleToStorageIndex;
    std::unordered_map<std::filesystem::path, AssetHandle> m_pathToHandle;

private:
    const AssetMetadata* GetMetadataOrNullptr(const AssetHandle& handle) const;
};