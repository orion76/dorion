<?php


/**
 * Implements hook_preprocess_block().
 */
function dorion_preprocess_html(&$variables) {
  $current_path = \Drupal::service('path.current')->getPath();
  $parts = explode('/', $current_path);
  array_shift($parts);

  //  $route_name = \Drupal::routeMatch()->getRouteName();

  switch($parts[0]){
    case 'admin':
      $variables['attributes']['class'][]='path-admin';
      break;
  }


  $n = 0;
  //  $theme = \Drupal::theme()->getActiveTheme()->getName();
  //  foreach (RegionSettings::getNavbarRegions($theme) as $region_id => $title) {
  //    if (empty($variables['page'][$region_id])) {
  //      continue;
  //    }
  //    RegionSettings::setPlacement($variables['page'][$region_id]);
  //    RegionSettings::setNavbarCollapsible($variables['page'][$region_id]);
  //  }

}
