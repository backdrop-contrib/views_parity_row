<?php

// Until I find a better solution...
include('views_parity_row_base.inc');

/**
 * @file
 * Contains the Views Parity Row row style plugin.
 */

/**
 * Plugin which performs a node_view on the resulting object.
 *
 * Most of the code on this object is in the theme function.
 *
 * @ingroup views_row_plugins
 */
class views_parity_row_plugin_row_node_parity_view extends views_plugin_row_node_view {
  use views_parity_row_base;

  function render($row) {
    if (isset($this->nodes[$row->{$this->field_alias}])) {
      $node = $this->nodes[$row->{$this->field_alias}];
      $node->view = $this->view;
      $view_mode = $this->find_view_mode($this->options, $this->view->row_index);

      $build = node_view($node, $view_mode);

      return drupal_render($build);
    }
  }
}
