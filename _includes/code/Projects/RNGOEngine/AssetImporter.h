namespace RNGOEngine::AssetHandling
{
    enum class ImportingError
    {
        None,
        FileNotFound,
        UnsupportedFormat,
        MalformedFile,
        UnknownError,
    };

    class AssetImporter
    {
    public:
        virtual ~AssetImporter() = default;

        virtual ImportingError LoadFromDisk(RuntimeAssetRegistry& registry, const AssetMetadata& metadata) = 0;
        virtual ImportingError FinalizeLoad(Data::ThreadType threadType, RuntimeAssetRegistry& registry) = 0;

        virtual void Unload(const AssetHandle& handle) = 0;

        virtual std::unique_ptr<AssetMetadata> CreateDefaultMetadata(
            const std::filesystem::path& path
        ) const = 0;

    public:
        virtual std::span<const std::string_view> GetSupportedExtensions() const = 0;
        virtual Data::ThreadType GetFinalizationThreadTypes() const = 0;
        virtual AssetType GetAssetType() const = 0;
    };
}