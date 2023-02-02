#include "AddIDs.hpp"

#include <Geode/Bindings.hpp>
#include <Geode/modify/EditLevelLayer.hpp>
#include <Geode/utils/cocos.hpp>
#include <Geode/ui/BasedButtonSprite.hpp>

USE_GEODE_NAMESPACE();

$register_ids(EditLevelLayer) {
    setIDs(
        this,
        0,
        "background",
        "bottom-left-art",
        "bottom-right-art",
        "level-name-background",
        "level-name-input",
        "description-background",
        "description-input",
        "description-text-area",
        "level-action-menu",
        "level-length",
        "level-song",
        "level-verified",
        "version-label",
        "level-id-label",
        "right-side-menu",
        "back-button-menu",
        "info-button-menu"
    );

    if (auto menu = this->getChildByID("level-action-menu")) {
        setIDs(menu, 0, "edit-button", "play-button", "share-button");
    }

    if (auto menu = this->getChildByID("right-side-menu")) {
        setIDs(
            menu,
            0,
            "delete-button",
            "help-button",
            "duplicate-button",
            "move-to-top-button",
            "folder-button"
        );

        detachAndCreateMenu(
            this, "folder-menu", ColumnLayout::create(), menu->getChildByID("folder-button")
        );
        menu->setPosition(
            menu->getPositionX() + static_cast<CCNode*>(
                menu->getChildren()->firstObject()
            )->getPositionX(),
            285.f
        );
        menu->setLayout(
            ColumnLayout::create()
                ->setGap(7.f)
                ->setReverse(true)
                ->setAlignment(Alignment::Begin)
                ->setAlignHorizontally(0.f)
        );
        menu->setZOrder(1);

        for (int i = 0; i < rand() % 4; i++) {
            auto btn = CircleButtonSprite::create(
                CCLabelBMFont::create(std::to_string(i).c_str(), "bigFont.fnt")
            );
            menu->addChild(btn);
        }
        menu->updateLayout();
    }

    if (auto menu = this->getChildByID("back-button-menu")) setIDSafe(menu, 0, "back-button");

    if (auto menu = this->getChildByID("info-button-menu")) setIDSafe(menu, 0, "info-button");
}

struct EditLevelLayerIDs : Modify<EditLevelLayerIDs, EditLevelLayer> {
    static void onModify(auto& self) {
        if (!self.setHookPriority("EditLevelLayer::init", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set EditLevelLayer::init hook priority, node IDs may not work properly");
        }
    }

    bool init(GJGameLevel* l) {
        if (!EditLevelLayer::init(l)) return false;

        NodeIDs::get()->provide(this);

        return true;
    }
};
