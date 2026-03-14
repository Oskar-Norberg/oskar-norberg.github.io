const dropdownHeadClassName = "selectable-dropdown";
const dropdownButtonClassName = "selectable-dropdown-button";
const dropdownAreaClassName = "selectable-dropdown-area";

const dropdownButtonNameAttribute = "data-dropdown-selectable-name";
const dropdownTextNameAttribute = "data-code-text-name";

const dropdownTextClassName = "selectable-text";
const dropdownTextEnabledClassName = "selectable-text-enabled";

const dropdownButtonActiveClass = "active";
const dropdownButtonDisabledClass = "disabled";

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
                        const isActive = textToOpen.classList.contains(dropdownTextEnabledClassName);

                        // Disable all texts
                        for (const key in selectableTexts) {
                            selectableTexts[key].classList.remove(dropdownTextEnabledClassName);
                        }

                        // Reset all buttons
                        for (const btn of selectable.querySelectorAll(`[${dropdownButtonNameAttribute}]`)) {
                            btn.classList.remove(dropdownButtonActiveClass);
                            btn.classList.remove(dropdownButtonDisabledClass);
                            btn.classList.add(dropdownButtonDisabledClass);
                        }

                        if (!isActive) {
                            // Enable text
                            textToOpen.classList.add(dropdownTextEnabledClassName);

                            // Set active button
                            child.classList.remove(dropdownButtonDisabledClass);
                            child.classList.add(dropdownButtonActiveClass);
                        }
                    });
                }
            }
        };
    };
});