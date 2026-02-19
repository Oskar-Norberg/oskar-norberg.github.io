struct MeshRenderer
{
    AssetHandling::AssetHandle ModelHandle;
    AssetHandling::AssetHandle MaterialKey;
};

struct Transform
{
    glm::vec3 Position = {0.0f, 0.0f, 0.0f};
    glm::quat Rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
    glm::vec3 Scale = {1.0f, 1.0f, 1.0f};

    glm::mat4 GetMatrix() const;
};

struct Camera
{
    float FOV = 45.0f;
    float NearPlane = 0.1f;
    float FarPlane = 100.0f;
};

struct LightFalloff
{
    // Standard range is 100
    // https://wiki.ogre3d.org/tiki-index.php?page=-Point+Light+Attenuation
    float Constant = 1.0f;
    float Linear = 0.045f;
    float Quadratic = 0.0075f;
};