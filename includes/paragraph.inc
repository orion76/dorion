<?php

use Drupal\block\Entity\Block;


/**
 * Implements hook_preprocess_block().
 */
function dorion_preprocess_paragraph(&$variables) {
  $n = 0;
  $variables['attributes']['class'][] = 'paragraph';
}
