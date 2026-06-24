
#[derive(Clone)]
pub enum Node {
    Variable(char),
    Not(Box<Node>),
    And(Box<Node>, Box<Node>),
    Or(Box<Node>, Box<Node>),
}

fn node_to_string(node: Node) -> String {
    match node {
        Node::Variable(c) => c.to_string(),
        Node::Not(inner) => format!("{}!", node_to_string(*inner)),
        Node::And(a, b) => format!("{}{}&", node_to_string(*a), node_to_string(*b)),
        Node::Or(a, b) => format!("{}{}|", node_to_string(*a), node_to_string(*b)),
    }
}


fn to_nnf(node: Node) -> Node {
    match node {
        Node::Not(inner) => match *inner {
            Node::Not(inner_inner) => to_nnf(*inner_inner),
            Node::And(a, b) => Node::Or(
                Box::new(to_nnf(Node::Not(a))),
                Box::new(to_nnf(Node::Not(b))),
            ),
            Node::Or(a, b) => Node::And(
                Box::new(to_nnf(Node::Not(a))),
                Box::new(to_nnf(Node::Not(b))),
            ),
            Node::Variable(c) => Node::Not(Box::new(Node::Variable(c))),
        },
        Node::And(a, b) => Node::And(Box::new(to_nnf(*a)), Box::new(to_nnf(*b))),
        Node::Or(a, b) => Node::Or(Box::new(to_nnf(*a)), Box::new(to_nnf(*b))),
        Node::Variable(c) => Node::Variable(c),
    }
}

pub fn negation_normal_form(formula: &str) -> String {
    let mut stack: Vec<Node> = Vec::new();

    for token in formula.chars() {
        match token {
            'A'..='Z' => stack.push(Node::Variable(token)),
            '!' => {
                let a = stack.pop().unwrap();
                stack.push(Node::Not(Box::new(a)));
            }
            '&' => {
                let b = stack.pop().unwrap();
                let a = stack.pop().unwrap();
                stack.push(Node::And(Box::new(a), Box::new(b)));
            }
            '|' => {
                let b = stack.pop().unwrap();
                let a = stack.pop().unwrap();
                stack.push(Node::Or(Box::new(a), Box::new(b)));
            }
            '>' => {
                let b = stack.pop().unwrap();
                let a = stack.pop().unwrap();
                stack.push(Node::Or(Box::new(Node::Not(Box::new(a))), Box::new(b)));
            }
            '^' => {
                let b = stack.pop().unwrap();
                let a = stack.pop().unwrap();
                let left = Node::And(Box::new(a.clone()), Box::new(Node::Not(Box::new(b.clone()))));
                let right = Node::And(Box::new(Node::Not(Box::new(a))), Box::new(b));
                stack.push(Node::Or(Box::new(left), Box::new(right)));
            }
            '=' => {
                let b = stack.pop().unwrap();
                let a = stack.pop().unwrap();
                let left = Node::And(Box::new(a.clone()), Box::new(b.clone()));
                let right = Node::And(Box::new(Node::Not(Box::new(a))), Box::new(Node::Not(Box::new(b))));
                stack.push(Node::Or(Box::new(left), Box::new(right)));
            }
            ' ' => continue,
            _ => panic!("Invalid characters"),
        }
    }

    if stack.len() != 1 {
        panic!("Invalid formula input");
    }
    let final_tree = stack.pop().unwrap();
    let nnf_tree = to_nnf(final_tree);
    node_to_string(nnf_tree)
}