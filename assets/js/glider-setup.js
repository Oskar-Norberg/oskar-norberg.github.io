document.addEventListener("DOMContentLoaded", function () {
    const glideElements = document.querySelectorAll('.glide');

    glideElements.forEach((el) => {
        new Glide(el, {
            type: 'carousel',
            perView: 3,
            focusAt: 'center'
        }).mount();
    });
});
