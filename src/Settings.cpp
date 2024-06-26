#include "Settings.h"
#include "Cache.h"
#include "Conditions.h"
#include <SimpleIni.h>
#include <sstream>

Settings* Settings::GetSingleton()
{
    static Settings settings;
    return &settings;
}

void Settings::LoadSettings()
{
    CSimpleIniA ini;
    ini.SetUnicode();
    ini.LoadFile(R"(.\Data\SKSE\Plugins\ValorPerks.ini)");

    enableSneakStaminaCost = ini.GetBoolValue("", "bEnableSneakStaminaCost", true);
    zeroAllWeapStagger     = ini.GetBoolValue("", "bZeroAllWeaponStagger", true);
    armorScalingEnabled    = ini.GetBoolValue("", "bArmorRatingScalingEnabled", true);

    std::string attackingSpellFormID((ini.GetValue("", "IsAttackingSpellFormId", "")));
    std::string blockingSpellFormID((ini.GetValue("", "IsBlockingSpellFormId", "")));
    std::string sneakingSpellFormID((ini.GetValue("", "IsSneakingSpellFormId", "")));
    std::string sprintingSpellFormId((ini.GetValue("", "IsSprintingSpellFormId", "")));
    std::string mountSprintingSpellFormId((ini.GetValue("", "MountSprintingSpellFormId", "")));
    std::string bowStaminaSpellFormID((ini.GetValue("", "BowStaminaSpellFormId", "")));
    std::string xbowStaminaSpellFormID((ini.GetValue("", "XbowStaminaSpellFormId", "")));
    std::string IsCastingFormId((ini.GetValue("", "IsCastingSpellFormId", "")));
    std::string bashPerkFormId((ini.GetValue("", "BashStaminaPerkFormId", "")));
    std::string blockPerkFormId((ini.GetValue("", "BlockStaminaPerkFormId", "")));
    std::string blockStaggerPerkFormId((ini.GetValue("", "BlockStaggerPerkFormId", "")));
    // new
    std::string parryControllerSpellID((ini.GetValue("", "MAGParryControllerSpellID", "")));
    std::string parryStaggerSpellID((ini.GetValue("", "MAGParryStaggerSpellFormID", "")));
    std::string BlockStaggerSpellID1((ini.GetValue("", "MAGBlockStaggerSpellFormID", "")));
    std::string BlockStaggerSpellID2((ini.GetValue("", "MAGBlockStaggerSpell2FormID", "")));
    std::string CrossbowStaminaDrainSpellID((ini.GetValue("", "MAGCrossbowStaminaDrainSpellFormID", "")));
    std::string parryWindowEffectID((ini.GetValue("", "MAG_ParryWindowEffectFormID", "")));
    std::string apoParryBuffSpellID((ini.GetValue("", "ParryBuffSpellFormID", "")));
    std::string APOSparksNormalBlockID((ini.GetValue("", "NormalBlockSparksID", "")));
    std::string APOSparksPhysicsBlockID((ini.GetValue("", "PhysicBlockSparksID", "")));
    std::string APOSparksFlashID((ini.GetValue("", "FlashBlockSparksID", "")));
    std::string APOSparksShieldFlashID((ini.GetValue("", "ShieldFlashBlockSparksID", "")));
    std::string jumpSpellID((ini.GetValue("", "JumpSpellID", "")));
    std::string powerAtkStopSpellID((ini.GetValue("", "PowerAttackStopSpellID", "")));
    std::string staminaCostGlobalID(ini.GetValue("", "APO_AttackStaminaCost", ""));
    std::string staminaCostNPCGlobalID(ini.GetValue("", "APO_NPCAttackStaminaCost", ""));

    std::string fileName(ini.GetValue("", "sModFileName", ""));

    auto bonusXP = (float)ini.GetDoubleValue("", "fBonusXPPerLevel", 0.15);
    auto baseXP  = (float)ini.GetDoubleValue("", "fBaseXPHerHit", 3.0);

    (bonusXP < 0.0 || bonusXP > 100.0) ? BonusXPPerLevel = 0.15f : BonusXPPerLevel = bonusXP;
    baseXP < 0.0 ? BaseXP = 3.0f : BaseXP = baseXP;

    if (!staminaCostGlobalID.empty()) {
        APOStaminaCostGlobalFormID = ParseFormID(staminaCostGlobalID);
    }
    if (!staminaCostNPCGlobalID.empty()) {
        APOStaminaCostNPCGlobalFormID = ParseFormID(staminaCostNPCGlobalID);
    }

    if (!attackingSpellFormID.empty()) {
        IsAttackingSpellFormId = ParseFormID(attackingSpellFormID);
    }

    if (!powerAtkStopSpellID.empty()) {
        APOPowerAttackStopSpellFormID = ParseFormID(powerAtkStopSpellID);
    }

    if (!jumpSpellID.empty()) {
        APOJumpSpellFormID = ParseFormID(jumpSpellID);
    }

    if (!blockingSpellFormID.empty()) {
        IsBlockingSpellFormId = ParseFormID(blockingSpellFormID);
    }

    if (!sneakingSpellFormID.empty()) {
        IsSneakingSpellFormId = ParseFormID(sneakingSpellFormID);
    }

    if (!sprintingSpellFormId.empty()) {
        IsSprintingSpellFormId = ParseFormID(sprintingSpellFormId);
    }

    if (!mountSprintingSpellFormId.empty()) {
        MountSprintingSpellFormId = ParseFormID(mountSprintingSpellFormId);
    }

    if (!bowStaminaSpellFormID.empty()) {
        BowDrainStaminaFormId = ParseFormID(bowStaminaSpellFormID);
    }

    if (!xbowStaminaSpellFormID.empty()) {
        XbowDrainStaminaFormId = ParseFormID(xbowStaminaSpellFormID);
    }

    if (!IsCastingFormId.empty()) {
        IsCastingSpellFormId = ParseFormID(IsCastingFormId);
    }

    if (!bashPerkFormId.empty()) {
        BashPerkFormId = ParseFormID(bashPerkFormId);
    }

    if (!blockPerkFormId.empty()) {
        BlockPerkFormId = ParseFormID(blockPerkFormId);
    }

    if (!blockStaggerPerkFormId.empty()) {
        BlockStaggerPerkFormId = ParseFormID(blockStaggerPerkFormId);
    }
    // new

    if (!parryControllerSpellID.empty()) {
        MAGParryControllerSpellID = ParseFormID(parryControllerSpellID);
    }
    if (!parryStaggerSpellID.empty()) {
        MAGParryStaggerSpellFormID = ParseFormID(parryStaggerSpellID);
    }
    if (!BlockStaggerSpellID1.empty()) {
        MAGBlockStaggerSpellFormID = ParseFormID(BlockStaggerSpellID1);
    }
    if (!BlockStaggerSpellID2.empty()) {
        MAGBlockStaggerSpell2FormID = ParseFormID(BlockStaggerSpellID2);
    }
    if (!CrossbowStaminaDrainSpellID.empty()) {
        MAGCrossbowStaminaDrainSpellFormID = ParseFormID(CrossbowStaminaDrainSpellID);
    }
    if (!parryWindowEffectID.empty()) {
        MAG_ParryWindowEffectFormID = ParseFormID(parryWindowEffectID);
    }
    if (!apoParryBuffSpellID.empty()) {
        APOParryBuffSpellFormID = ParseFormID(apoParryBuffSpellID);
    }
    if (!APOSparksNormalBlockID.empty()) {
        APONormalBlockSparksFormID = ParseFormID(APOSparksNormalBlockID);
    }
    if (!APOSparksPhysicsBlockID.empty()) {
        APOPhysicBlockSparksFormID = ParseFormID(APOSparksPhysicsBlockID);
    }
    if (!APOSparksFlashID.empty()) {
        APOFlashSparksFormID = ParseFormID(APOSparksFlashID);
    }
    if (!APOSparksShieldFlashID.empty()) {
        APOShieldFlashSparksFormID = ParseFormID(APOSparksShieldFlashID);
    }

    FileName = fileName;
}

RE::FormID Settings::ParseFormID(const std::string& str)
{
    RE::FormID         result;
    std::istringstream ss{ str };
    ss >> std::hex >> result;
    return result;
}

void Settings::AdjustWeaponStaggerVals()
{
    if (zeroAllWeapStagger) {
        logger::info("Adjusting weapon stagger values");
        int16_t totalWeaps = 0;

        auto dataHandler = RE::TESDataHandler::GetSingleton();
        if (dataHandler) {
            for (const auto& foundWeap : dataHandler->GetFormArray<RE::TESObjectWEAP>()) {
                if (foundWeap && !foundWeap->weaponData.flags.any(RE::TESObjectWEAP::Data::Flag::kNonPlayable)) {
                    foundWeap->weaponData.staggerValue = 0.0f;
                    totalWeaps++;
                }
            }
        }

        logger::info(FMT_STRING("Stagger values adjusted: {} weapons"), totalWeaps);
    }
}

void Settings::LoadForms()
{
    auto dataHandler = RE::TESDataHandler::GetSingleton();

    auto file = dataHandler->LookupLoadedModByName(FileName);
    ;

    if (!file || file->compileIndex == 0xFF) {
        SKSE::stl::report_and_fail("Cannot find ValorPerks.esp. If you are on Skyrim 1.6.1130+, Engine Fixes' achievements enabler may be disabling all of your plugins."sv);
    }
    logger::info("Loading forms");
    if (APOStaminaCostGlobalFormID) {
        StaminaCostGlobal = skyrim_cast<RE::TESGlobal*>(dataHandler->LookupForm(APOStaminaCostGlobalFormID, FileName));
    }
    if (APOStaminaCostNPCGlobalFormID) {
        NPCStaminaCostGlobal = skyrim_cast<RE::TESGlobal*>(dataHandler->LookupForm(APOStaminaCostNPCGlobalFormID, FileName));
        logger::info("global {} found it is a value of {}", NPCStaminaCostGlobal->GetFormEditorID(), NPCStaminaCostGlobal->value);
    }
    if (IsBlockingSpellFormId)
        IsBlockingSpell = skyrim_cast<RE::SpellItem*>(dataHandler->LookupForm(IsBlockingSpellFormId, FileName));

    if (APOPowerAttackStopSpellFormID)
        PowerAttackStopSpell = skyrim_cast<RE::SpellItem*>(dataHandler->LookupForm(APOPowerAttackStopSpellFormID, FileName));

    if (APOJumpSpellFormID)
        jumpSpell = skyrim_cast<RE::SpellItem*>(dataHandler->LookupForm(APOJumpSpellFormID, FileName));

    if (IsAttackingSpellFormId)
        IsAttackingSpell = skyrim_cast<RE::SpellItem*>(dataHandler->LookupForm(IsAttackingSpellFormId, FileName));

    if (IsSneakingSpellFormId)
        IsSneakingSpell = skyrim_cast<RE::SpellItem*>(dataHandler->LookupForm(IsSneakingSpellFormId, FileName));

    if (IsSprintingSpellFormId)
        IsSprintingSpell = skyrim_cast<RE::SpellItem*>(dataHandler->LookupForm(IsSprintingSpellFormId, FileName));

    if (MountSprintingSpellFormId)
        MountSprintingSpell = skyrim_cast<RE::SpellItem*>(dataHandler->LookupForm(MountSprintingSpellFormId, FileName));

    if (BowDrainStaminaFormId)
        BowStaminaSpell = skyrim_cast<RE::SpellItem*>(dataHandler->LookupForm(BowDrainStaminaFormId, FileName));

    if (XbowDrainStaminaFormId)
        XbowStaminaSpell = skyrim_cast<RE::SpellItem*>(dataHandler->LookupForm(XbowDrainStaminaFormId, FileName));

    if (IsCastingSpellFormId)
        IsCastingSpell = skyrim_cast<RE::SpellItem*>(dataHandler->LookupForm(IsCastingSpellFormId, FileName));

    if (BashPerkFormId)
        BashStaminaPerk = dataHandler->LookupForm(BashPerkFormId, "Update.esm")->As<RE::BGSPerk>();

    if (BlockPerkFormId)
        BlockStaminaPerk = dataHandler->LookupForm(BlockPerkFormId, "Update.esm")->As<RE::BGSPerk>();

    if (BlockStaggerPerkFormId)
        BlockStaggerPerk = dataHandler->LookupForm(BlockStaggerPerkFormId, "Update.esm")->As<RE::BGSPerk>();

    if (MAGParryControllerSpellID)
        MAGParryControllerSpell = skyrim_cast<RE::SpellItem*>(dataHandler->LookupForm(MAGParryControllerSpellID, FileName));

    if (MAGParryStaggerSpellFormID)
        MAGParryStaggerSpell = skyrim_cast<RE::SpellItem*>(dataHandler->LookupForm(MAGParryStaggerSpellFormID, FileName));

    if (MAGBlockStaggerSpellFormID)
        MAGBlockStaggerSpell = skyrim_cast<RE::SpellItem*>(dataHandler->LookupForm(MAGBlockStaggerSpellFormID, FileName));

    if (MAGBlockStaggerSpell2FormID)
        MAGBlockStaggerSpell2 = skyrim_cast<RE::SpellItem*>(dataHandler->LookupForm(MAGBlockStaggerSpell2FormID, FileName));

    if (MAGCrossbowStaminaDrainSpellFormID)
        MAGCrossbowStaminaDrainSpell = skyrim_cast<RE::SpellItem*>(dataHandler->LookupForm(MAGCrossbowStaminaDrainSpellFormID, FileName));

    if (MAG_ParryWindowEffectFormID)
        MAG_ParryWindowEffect = skyrim_cast<RE::EffectSetting*>(dataHandler->LookupForm(MAG_ParryWindowEffectFormID, FileName));

    if (APOParryBuffSpellFormID)
        APOParryBuffSPell = skyrim_cast<RE::SpellItem*>(dataHandler->LookupForm(APOParryBuffSpellFormID, FileName));

    if (APONormalBlockSparksFormID)
        APOSparks = skyrim_cast<RE::BGSExplosion*>(dataHandler->LookupForm(APONormalBlockSparksFormID, FileName));

    if (APOPhysicBlockSparksFormID)
        APOSparksPhysics = skyrim_cast<RE::BGSExplosion*>(dataHandler->LookupForm(APOPhysicBlockSparksFormID, FileName));

    if (APOFlashSparksFormID)
        APOSparksFlash = skyrim_cast<RE::BGSExplosion*>(dataHandler->LookupForm(APOFlashSparksFormID, FileName));

    if (APOShieldFlashSparksFormID)
        APOSparksShieldFlash = skyrim_cast<RE::BGSExplosion*>(dataHandler->LookupForm(APOShieldFlashSparksFormID, FileName));

    SetGlobalsAndGameSettings();

    auto isPowerAttacking                        = new RE::TESConditionItem;
    isPowerAttacking->data.comparisonValue.f     = 1.0f;
    isPowerAttacking->data.functionData.function = RE::FUNCTION_DATA::FunctionID::kIsPowerAttacking;

    auto isPowerAttackingCond  = new RE::TESCondition;
    isPowerAttackingCond->head = isPowerAttacking;
    IsPowerAttacking           = isPowerAttackingCond;

    logger::info("All Forms loaded");
}

void Settings::SetGlobalsAndGameSettings()
{
    // Set fMaxArmorRating game setting
    auto gameSettings     = RE::GameSettingCollection::GetSingleton();
    auto maxRatingSetting = gameSettings->GetSetting("fMaxArmorRating");

    if (armorScalingEnabled) {
        logger::info("Setting max armor rating to 90");
        maxRatingSetting->data.f = 90.0f;
    }
    else {
        logger::info("Setting max armor rating to 75");
        maxRatingSetting->data.f = 75.0f;
    }
}
