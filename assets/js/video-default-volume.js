const DEFAULT_VOLUME = 0.33;

function setVolume(video) {
    if (!video) {
        return;
    }

    const apply = () => video.volume = DEFAULT_VOLUME;

    if (video.readyState >= 1) {
        apply();
    } else {
        video.addEventListener('loadedmetadata', apply, { once: true });
    }
}

// Statically loaded videos
document.querySelectorAll('video').forEach(setVolume);

// Dynamically loaded videos
const observer = new MutationObserver((mutations) => {
    for (const mutation of mutations) {
        for (const node of mutation.addedNodes) {
            if (node.nodeType !== 1) continue;

            if (node.tagName === 'VIDEO') {
                setVolume(node);
            } else {
                node.querySelectorAll?.('video').forEach(setVolume);
            }
        }
    }
});

if (document.body) {
    observer.observe(document.body, { childList: true, subtree: true });
}