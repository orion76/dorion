<?php

use Drupal\block\BlockRepositoryInterface;

class RegionSettings {


  static function setPlacement(&$variables) {
    $theme = \Drupal::theme()->getActiveTheme()->getName();
    $region = $variables['region'];
    $opt_name = ThemeSettings::getName($theme, SettingsIds::REGION_PLACEMENT, $region);
    $variables['placement'] = theme_get_setting($opt_name);
  }

  static function setNavbarCollapsible(&$variables) {
    $theme = \Drupal::theme()->getActiveTheme()->getName();
    $region = $variables['region'];
    $opt_name = ThemeSettings::getName($theme, SettingsIds::NAVBAR_COLLAPSIBLE, $region);
    $variables['collapsible'] = theme_get_setting($opt_name);
    $variables['collapse_class'] = $region . "__collapse";
  }

  static function getPlacementOptions() {
    return [
      'default' => t('Default'),
      'fixed-top' => t('Fixed Top'),
      'fixed-bottom' => t('Fixed Bottom'),
      'sticky-top' => t('Sticky Top'),
    ];
  }

  static function isNavbar($name) {
    return strpos($name, 'navbar_') === 0;
  }

  static function getNavbarRegions($theme) {
    $region_list = system_region_list($theme, $show = BlockRepositoryInterface::REGIONS_ALL);
    $navbars = [];
    foreach ($region_list as $id => $title) {
      if (static::isNavbar($id)) {
        $navbars[$id] = $title;
      }
    }
    return $navbars;
  }
}
