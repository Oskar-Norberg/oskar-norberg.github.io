const MOBILE_PER_VIEW = 2
const DESKTOP_PER_VIEW = 3
const MOBILE_SIZE_BREAKPOINT = 800

document.addEventListener("DOMContentLoaded", function () {
    const glideElements = document.querySelectorAll('.glide');
    const glides = [];

    function createGlide(el, perView) {
        return new Glide(el, {
            type: 'carousel',
            perView: perView,
            focusAt: 'center'
        });
    }

    function updateGlides() {
        const isMobile = window.innerWidth <= MOBILE_SIZE_BREAKPOINT;
        const perView = isMobile ? MOBILE_PER_VIEW : DESKTOP_PER_VIEW;

        glideElements.forEach((el, index) => {
            const currentGlide = glides[index];

            if (currentGlide && currentGlide.settings.perView !== perView) {
                currentGlide.destroy();
                const newGlide = createGlide(el, perView);
                newGlide.mount();
                glides[index] = newGlide;
            }

            if (!currentGlide) {
                const newGlide = createGlide(el, perView);
                newGlide.mount();
                glides[index] = newGlide;
            }
        });
    }

    updateGlides();

    window.addEventListener('resize', updateGlides);
});
