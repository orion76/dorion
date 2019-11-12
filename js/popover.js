(function ($, Drupal) {

  'use strict';

  Drupal.behaviors.dorionPopover = {
    attach: function (context) {
      $('[data-toggle="popover"]').popover();
    }
  };

})(jQuery, Drupal);
