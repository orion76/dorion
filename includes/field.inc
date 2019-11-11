<?php

/**
 * @file
 * Theme and preprocess functions for fields.
 */

use Drupal\Component\Utility\Html;

/**
 * Implements hook_preprocess_field().
 */
function dorion_preprocess_field(&$variables) {
  $element = $variables['element'];
  $field_name = $element['#field_name'];
  $field_type = $variables['element']['#field_type'];

  $variables['attributes']['class'][] = 'field';
  $variables['attributes']['class'][] = Html::cleanCssIdentifier('field-type--' . $field_type);


  $bundle = $element['#bundle'];

  // Add bundle to template.
  $variables['bundle'] = $bundle;

  // Add a clean field name without the field_BUNDLE_ prefix.
  $safe_field_name_prefix = 'field_' . $bundle . '_';
  $variables['field_name_clean'] = str_replace($safe_field_name_prefix, '', $field_name);
}

/**
 * Implements template_preprocess_filter_caption().
 */
function dorion_preprocess_filter_caption(&$variables) {
  // Do this for img tags only.
  if (($variables['tag'] !== 'img')) {
    return;
  }

  // Add the figure-img class to the rendered image markup.
  libxml_use_internal_errors(TRUE);
  $doc = new DOMDocument();
  $doc->loadHTML($variables['node']);
  if ($image = $doc->getElementsByTagName('img')->item(0)) {
    $image->setAttribute('class', 'figure-img img-fluid');
    $variables['node'] = [
      '#markup' => $image->ownerDocument->saveHTML($image),
    ];
  }
}
