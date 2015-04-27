<?php

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

  function option_definition() {
    $options = parent::option_definition();

    $options['views_parity_row']['enable'] = array('default' => FALSE, 'bool' => TRUE);
    $options['views_parity_row']['odd']['view_mode'] = array('default' => 'teaser');
    $options['views_parity_row']['even']['view_mode'] = array('default' => 'teaser');

    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $options = $this->options_form_summary_options();
    $form['view_mode'] = array(
      '#type' => 'select',
      '#options' => $options,
      '#title' => t('View mode'),
      '#default_value' => $this->options['view_mode'],
    );
    $form['links'] = array(
      '#type' => 'checkbox',
      '#title' => t('Display links'),
      '#default_value' => $this->options['links'],
    );
    $form['comments'] = array(
      '#type' => 'checkbox',
      '#title' => t('Display comments'),
      '#default_value' => $this->options['comments'],
    );
    $form['views_parity_row']['enable'] = array(
      '#type' => 'checkbox',
      '#title' => t('Enable a different view mode for odd and even rows ?'),
      '#default_value' => $this->options['views_parity_row']['enable'],
    );

    $form['views_parity_row']['even'] = array(
      '#type' => 'fieldset',
      '#title' => t('Configuration for even rows (0, 2, 4, 6, ...)'),
      '#states' => array(
        'visible' => array(
          ':input[name="row_options[views_parity_row][enable]"]' => array('checked' => TRUE),
        ),
      ),
      'view_mode' => array(
        '#type' => 'select',
        '#options' => $options,
        '#title' => t('View mode'),
        '#default_value' => $this->options['views_parity_row']['even']['view_mode'],
      ),
    );

    $form['views_parity_row']['odd'] = array(
      '#type' => 'fieldset',
      '#title' => t('Configuration for odd rows (1, 3, 5, 7, ...)'),
      '#states' => array(
        'visible' => array(
          ':input[name="row_options[views_parity_row][enable]"]' => array('checked' => TRUE),
        ),
      ),
      'view_mode' => array(
        '#type' => 'select',
        '#options' => $options,
        '#title' => t('View mode'),
        '#default_value' => $this->options['views_parity_row']['odd']['view_mode'],
      ),
    );

  }

  function render($row) {
    if (isset($this->nodes[$row->{$this->field_alias}])) {
      $node = $this->nodes[$row->{$this->field_alias}];
      $node->view = $this->view;

      if ($this->options['views_parity_row']['enable'] == TRUE) {
        if ($this->view->row_index % 2 == 0) {
          $view_mode = $this->options['views_parity_row']['even']['view_mode'];
        } else {
          $view_mode = $this->options['views_parity_row']['odd']['view_mode'];
        }
      }

      $build = node_view($node, $view_mode);

      return drupal_render($build);
    }
  }
}
