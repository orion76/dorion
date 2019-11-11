<?php

use Drupal\Component\Utility\Html;
use Drupal\Core\Template\Attribute;

/**
 * Implements hook_theme_suggestions_HOOK_alter().
 */
function dorion_theme_suggestions_region_alter(array &$suggestions, array $variables) {
  if (RegionSettings::isNavbar($variables['elements']['#region'])) {
    $suggestions[] = 'region__navbar';
  }

}


/**
 * Implements hook_preprocess_block().
 */
function dorion_preprocess_region(&$variables) {
  $attributes = new Attribute();
  $attributes->addClass('region');
  $attributes->addClass(Html::cleanCssIdentifier('region__' . $variables['region'], ThemeSettings::getCssFilter()));
  $variables['attributes'] = $attributes;
  if (RegionSettings::isNavbar($variables['elements']['#region'])) {
    $attributes->addClass('region__navbar');
  }
  RegionSettings::setPlacement($variables);
  RegionSettings::setNavbarCollapsible($variables);
}
