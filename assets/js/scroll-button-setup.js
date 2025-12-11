const attributeName = "data-scroll-to";

const scrollToTopID = "home";

document.addEventListener("DOMContentLoaded", () => {
    const scrollButtons = document.querySelectorAll(`[${attributeName}]`);

    scrollButtons.forEach(button => {
        button.addEventListener("click", (event) => {
            const targetID = button.getAttribute(attributeName);
            const target = document.getElementById(targetID);

            if (!target) {
                if (targetID === scrollToTopID) {
                    window.scrollTo({ top: 0, behavior: "smooth" });
                }

                return;
            }

            event.preventDefault();

            target.scrollIntoView({ behavior: "smooth", block: "center" });

            history.replaceState(null, "", `#${targetID}`);
        });
    });
});

window.addEventListener("load", () => {
    const hash = window.location.hash;

    if (!hash) {
        return;
    }

    const target = document.querySelector(hash);
    if (!target) {
        return;
    }

    target.scrollIntoView({ behavior: "smooth", block: "start" });
});
