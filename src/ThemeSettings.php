<?php

$includes_path = dirname(__FILE__) . '/settings/*.php';
foreach (glob($includes_path) as $filename) {
  require_once dirname(__FILE__) . '/settings/' . basename($filename);
}


class ThemeSettings {

  static function getName($theme, $name, $suffix) {
    return "{$theme}__{$name}__{$suffix}";
  }

  static function getCssFilter() {
    return [
      ' ' => '_',
      '-' => '_',
      '/' => '_',
      '[' => '_',
      ']' => '',
    ];
  }
}
