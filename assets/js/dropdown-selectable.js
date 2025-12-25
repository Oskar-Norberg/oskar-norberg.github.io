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

        if (selectableArea == null) {
            console.error(`Selectable area of selectable ${selectable} is null`);
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
                    const textToOpen = childAttribute.value;

                    child.addEventListener("click", () => {
                        // TODO: If you disable the currently active one it should close entirely

                        for (const key in selectableTexts){
                            selectableTexts[key].classList.remove(dropdownTextEnabledClassName);
                        }
                        
                        if (!(textToOpen in selectableTexts)){
                            console.error(`Selectable named ${textToOpen} does not exist`);
                            return;
                        }

                        // Toggle active
                        const text = selectableTexts[textToOpen];

                        text.classList.add(dropdownTextEnabledClassName);
                    });
                }
            }
        };
    };
});