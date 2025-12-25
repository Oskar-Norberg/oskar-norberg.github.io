const dropdownHeadClassName = "selectable-dropdown";
const dropdownButtonClassName = "selectable-dropdown-button";
const dropdownAreaClassName = "selectable-dropdown-area";

const dropdownButtonNameAttribute = "data-dropdown-selectable-name";
const dropdownTextNameAttribute = "data-code-text-name";

const dropdownTextClassName = "selectable-text";
const dropdownTextEnabledClassName = "selectable-text-enabled";

document.addEventListener("DOMContentLoaded", () => {
    const selectables = document.querySelectorAll(`.${dropdownHeadClassName}`);

    for (const selectable of selectables) {
        // Get dropdown area and all texts in it
        var selectableArea = null;

        for (const child of selectable.children) {
            if (child.classList.contains(dropdownAreaClassName)) {
                selectableArea = child;
                break;
            }
        }

        if (!selectableArea) {
            alert(`Selectable area of selectable ${selectable} is null`);
            continue;
        }

        // Get all texts in Dropdown Area
        const selectableTexts = {};
        for (const child of selectableArea.children) {
            for (const childAttribute of child.attributes) {
                if (childAttribute.name === dropdownTextNameAttribute) {
                    selectableTexts[childAttribute.value] = child;
                }
            }
        }

        // Add Onclick events to each Button
        for (const child of selectable.children) {
            for (const childAttribute of child.attributes) {
                if (childAttribute.name === dropdownButtonNameAttribute) {
                    const attributeToOpen = childAttribute.value;

                    child.addEventListener("click", () => {
                        if (!(attributeToOpen in selectableTexts)) {
                            alert(`Selectable named ${attributeToOpen} does not exist`);
                            return;
                        }

                        const textToOpen = selectableTexts[attributeToOpen];

                        // If you try to enable the currently selected one, disable all.
                        if (textToOpen.classList.contains(dropdownTextEnabledClassName)) {
                            // Disable all
                            for (const key in selectableTexts) {
                                selectableTexts[key].classList.remove(dropdownTextEnabledClassName);
                            }
                        } else {
                            // Disable all
                            for (const key in selectableTexts) {
                                selectableTexts[key].classList.remove(dropdownTextEnabledClassName);
                            }

                            // Toggle active
                            const text = selectableTexts[attributeToOpen];

                            text.classList.add(dropdownTextEnabledClassName);
                        }
                    });
                }
            }
        };
    };
});