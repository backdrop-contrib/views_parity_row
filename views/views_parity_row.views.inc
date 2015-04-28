<?php

/**
 * Implements hook_views_plugins().
 */
function views_parity_row_views_plugins() {
  return array(
    'row' => array(
      'views_parity_row' => array(
        'title' => t('Content (alternate)'),
        'help' => t('Display the content with standard node view and alternate view mode according to the row index.'),
        'handler' => 'views_parity_row_plugin_row_node_parity_view',
        'path' => drupal_get_path('module', 'views_parity_row') . '/views',
        'base' => array('node'),
        'uses options' => TRUE,
        'type' => 'normal',
        'help topic' => 'style-node',
      ),
    ),
  );
}

