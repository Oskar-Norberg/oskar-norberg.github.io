namespace RNGOEngine::Core::Renderer
{
    class RenderPass
    {
    public:
        explicit RenderPass(IRenderer& renderer, const int width, const int height)
            : m_renderer(renderer), m_width(width), m_height(height)
        {
        }

    public:
        virtual ~RenderPass() = default;

    public:
        virtual void Execute(RenderContext& context) = 0;

    public:
        virtual Resources::RenderTargetSpecification GetRenderTargetSpecification() const = 0;

    public:
        virtual void OnResize(const int width, const int height)
        {
            m_width = width;
            m_height = height;
        }

    protected:
        IRenderer& m_renderer;
        int m_width, m_height;
    };
}