<?php

/**
 * @file
 * Theme and preprocess functions for block.
 */

use Drupal\block\Entity\Block;
use Drupal\Core\Render\Element;

/**
 * Implements hook_theme_suggestions_HOOK_alter().
 */
function dorion_theme_suggestions_block_alter(array &$suggestions, array $variables) {
  // Check for BlockContent.
  if ($variables['elements']['#configuration']['provider'] != 'block_content' || empty($variables['elements']['content']['#block_content'])) {
    return;
  }

  // Get the block bundle.
  $block_content = $variables['elements']['content']['#block_content'];
  $bundle = $block_content->bundle();

  // Add to theme suggestions.
  $suggestions[] = 'block__block_content__' . $bundle;
}

/**
 * Implements hook_preprocess_block().
 */
function dorion_preprocess_block(&$variables) {
  // Add id to template.
  if (isset($variables['elements']['#id'])) {
    $variables['id'] = str_replace('_', '-', $variables['elements']['#id']);

    $block = Block::load($variables['elements']['#id']);
    $name = str_replace($block->getTheme() . "_", "", $block->id());
    $variables['attributes']['class'][] = 'block__' . $name;
  }
  if (isset($variables['id'])) {
    $n = 0;
  }
  // Check for BlockContent.
  if ($variables['elements']['#configuration']['provider'] != 'block_content' || empty($variables['elements']['content']['#block_content'])) {
    return;
  }

  // Get the block bundle.
  $block_content = $variables['elements']['content']['#block_content'];

  // Add bundle to template.
  $variables['bundle'] = $block_content->bundle();
}

/**
 * Implements template_preprocess_block_content().
 */
function dorion_preprocess_block_content(&$variables) {
  // Helpful $content variable for templates.
  $variables += ['content' => []];
  foreach (Element::children($variables['elements']) as $key) {
    $variables['content'][$key] = $variables['elements'][$key];
  }
}
