<?php

require_once dirname(__FILE__) . '/src/ThemeSettings.php';

/**
 * @file
 * theme-settings.php
 *
 * Provides theme settings for Bootstrap Barrio based themes when admin theme is not.
 *
 * @see ./includes/settings.inc
 */

use Drupal\block\BlockRepositoryInterface;
use Drupal\Core\Form\FormStateInterface;

function _dorion_form_system_theme_settings__regions_navbars($theme) {

  // * - placement: default | fixed-top | fixed-bottom | sticky-top

  $regions_navbar = [
    '#type' => 'details',
    '#title' => t('Navbar'),
    '#open' => TRUE,
  ];
  $placement_options = RegionSettings::getPlacementOptions();
  $navbars = RegionSettings::getNavbarRegions($theme);
  foreach ($navbars as $name => $description) {

    $regions_navbar[$name] = [
      '#type' => 'details',
      '#title' => $description,
      '#open' => TRUE,
    ];

    $navbar_collapsible_setting_name = ThemeSettings::getName($theme, SettingsIds::NAVBAR_COLLAPSIBLE, $name);
    $navbar_collapsible = theme_get_setting($navbar_collapsible_setting_name);
    $regions_navbar[$name][$navbar_collapsible_setting_name] = [
      '#type' => 'checkbox',
      '#title' => t('Collapsible'),
      '#default_value' => $navbar_collapsible === NULL ? FALSE : $navbar_collapsible,
    ];


    $placement_setting_name = ThemeSettings::getName($theme, SettingsIds::REGION_PLACEMENT, $name);
    $placement = theme_get_setting($placement_setting_name);
    $regions_navbar[$name][$placement_setting_name] = [
      '#type' => 'select',
      '#title' => t('Placement'),
      '#options' => $placement_options,
      '#default_value' => empty($placement) ? 'default' : $placement,
    ];


  }
  return $regions_navbar;
}

/**
 * Implements hook_form_FORM_ID_alter().
 *
 * @param $form
 * @param \Drupal\Core\Form\FormStateInterface $form_state
 * @param null $form_id
 */
function dorion_form_system_theme_settings_alter(&$form, FormStateInterface $form_state, $form_id = NULL) {

  // General "alters" use a form id. Settings should not be set here. The only
  // thing useful about this is if you need to alter the form for the running
  // theme and *not* the theme setting.
  // @see http://drupal.org/node/943212
  if (isset($form_id)) {
    return;
  }

  // List of regions
  $theme = \Drupal::theme()->getActiveTheme()->getName();
  $region_list = system_region_list($theme, $show = BlockRepositoryInterface::REGIONS_ALL);

  //Change collapsible fieldsets (now details) to default #open => FALSE.
  $form['theme_settings']['#open'] = FALSE;
  $form['logo']['#open'] = FALSE;
  $form['favicon']['#open'] = FALSE;

  // Vertical tabs
  $form['tabs'] = [
    '#type' => 'vertical_tabs',
    '#weight' => -10,
  ];

  $form['regions'] = [
    '#type' => 'details',
    '#title' => t('Regions'),
    '#group' => 'tabs',
  ];

  $form['regions']['navbars'] = _dorion_form_system_theme_settings__regions_navbars($theme);

  // General.

}
