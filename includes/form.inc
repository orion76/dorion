<?php
/**
 * @file
 * Theme and preprocess functions for forms.
 */

use Drupal\Core\Form\FormStateInterface;

/**
 * Implements hook_theme_suggestions_HOOK_alter().
 */
function dorion_theme_suggestions_form_alter(array &$suggestions, array &$variables) {
  $element = $variables['element'];

  // Add a suggestion based on the form id name.
  if (isset($element['#form_id'])) {
    $suggestions[] = $variables['theme_hook_original'] . '__' . $element['#form_id'];
  }
}

/**
 * Implements hook_theme_suggestions_HOOK_alter().
 */
function dorion_theme_suggestions_form_element_alter(array &$suggestions, array &$variables) {
  $element = $variables['element'];

  // Add a suggestion based on the element type.
  if (isset($element['#type'])) {
    $suggestions[] = $variables['theme_hook_original'] . '__' . $element['#type'];
  }
}

/**
 * Implements hook_preprocess_input().
 */
function dorion_preprocess_input(&$variables) {
  $element = &$variables['element'];

  // Add the element type to the theme.
  $variables['type'] = $element['#type'];
  if (isset($element['#description'])) {

    $variables['attributes'] += [
      'data-toggle' => 'popover',
      'data-placement' => 'right',
      'data-content' => $element['#description']->render(),
      'data-trigger' => 'hover',
    ];
    unset($element['#description']);
  }
}


/**
 * Implements hook_preprocess_form_element().
 */
function dorion_preprocess_form(&$variables) {
  array_unshift($variables['attributes']['class'], 'form');
  $element = $variables['element'];
}

/**
 * Implements hook_preprocess_form_element().
 */
function dorion_preprocess_form_element(&$variables) {
  $element = $variables['element'];

  if (isset($variables['description'])) {
    unset($variables['description']);
  }

  // Add required class for checkbox and radio labels.
  if (in_array($element['#type'], ['checkbox', 'radio'])) {
    $variables['label']['#attributes']['class'][] = 'form-check-label';
  }
}

/**
 * Implements hook_form_FORM_ID_alter().
 */
function dorion_form_search_block_form_alter(&$form, FormStateInterface $form_state, $form_id) {
  // Update the placeholder and size of field.
  $form['keys']['#title'] = '';
  $form['keys']['#size'] = 20;
  $form['keys']['#placeholder'] = t('Search');
}
