AOS.init({
    once: true,
});

const thumbsSwiper = new Swiper('.thumbs-swiper', {
    spaceBetween: 0,
    slidesPerView: 4,
    freeMode: true,
    watchSlidesProgress: true,
    slideToClickedSlide: true,
    loop: false,
});

const swiper = new Swiper('.main-swiper', {
    loop: true,
    pagination: {
        el: '.swiper-pagination',
        clickable: true,
    },
    navigation: {
        nextEl: '.swiper-button-next',
        prevEl: '.swiper-button-prev',
    },
    thumbs: {
        swiper: thumbsSwiper,
    },
    on: {
        slideChange: function () {
            pauseAllVideos();
        }
    }
});

function pauseAllVideos() {
    document.querySelectorAll('.main-swiper video').forEach(video => {
        video.pause();
    });
}